#include "symbol_table.hpp"
#include <algorithm>
#include <cctype>

SymbolTable::SymbolTable() {
  m_scope_stack.emplace_back();

  for (const PredefinedSymbol &s : predefined_symbols) {
    install_attribute(std::string{s.lexeme}, s.symbol_type, s.data_type,
                      s.token_type);
  }
}

bool SymbolTable::declare(const std::string &name, SymbolType symbol_type,
                          DataType data_type, TokenType token_type) {
  const std::string normalized_name{normalize_name(name)};

  if (declared_in_current_scope(normalized_name))
    return false;

  install_attribute(normalized_name, symbol_type, data_type, token_type);

  return true;
}

std::optional<std::size_t> SymbolTable::lookup(const std::string &name) const {
  const std::string normalized_name{normalize_name(name)};

  const auto name_entry{m_name_table.find(normalized_name)};

  if (name_entry == m_name_table.end())
    return std::nullopt;

  return name_entry->second.current_attribute_index;
}

std::optional<TokenType>
SymbolTable::lookup_predefined_token(const std::string &lexeme) const {
  const auto attribute_index{lookup(lexeme)};

  if (!attribute_index)
    return std::nullopt;

  const AttributeEntry &attribute{get_attribute(*attribute_index)};

  if (attribute.symbol_type != SymbolType::Keyword &&
      attribute.symbol_type != SymbolType::Operator) {
    return std::nullopt;
  }

  return attribute.token_type;
}

const AttributeEntry &
SymbolTable::get_attribute(std::size_t attribute_index) const {
  return m_attribute_table.at(attribute_index);
}

std::string SymbolTable::normalize_name(const std::string &name) {
  std::string normalized{name};

  std::transform(
      normalized.begin(), normalized.end(), normalized.begin(),
      [](unsigned char c) { return static_cast<char>(std::toupper(c)); });

  return normalized;
}

void SymbolTable::enter_scope() { m_scope_stack.emplace_back(); }

void SymbolTable::exit_scope() {
  if (m_scope_stack.size() == 1)
    throw std::logic_error("cannot exit the global scope");

  const Scope &current_scope{m_scope_stack.back()};

  for (auto name = current_scope.declared_names.rbegin();
       name != current_scope.declared_names.rend(); ++name) {
    NameEntry &name_entry{m_name_table.at(*name)};

    if (!name_entry.current_attribute_index)
      throw std::logic_error("symbol has no active attribute");

    const AttributeEntry &current_attribute{
        m_attribute_table.at(*name_entry.current_attribute_index)};

    name_entry.current_attribute_index =
        current_attribute.outer_attribute_index;
  }

  m_scope_stack.pop_back();
}

NameEntry &SymbolTable::install_name(const std::string &name) {
  const std::string normalized_name{normalize_name(name)};

  return m_name_table.try_emplace(normalized_name, NameEntry{}).first->second;
}

std::size_t SymbolTable::install_attribute(const std::string &name,
                                           SymbolType symbol_type,
                                           DataType data_type,
                                           TokenType token_type) {
  const std::string normalized_name{normalize_name(name)};
  NameEntry &name_entry{install_name(normalized_name)};

  const std::optional<std::size_t> outer_attribute_index{
      name_entry.current_attribute_index};

  const std::size_t attribute_index{m_attribute_table.size()};

  m_attribute_table.emplace_back(AttributeEntry{
      token_type,
      symbol_type,
      data_type,
      outer_attribute_index,
  });

  name_entry.current_attribute_index = attribute_index;

  m_scope_stack.back().declared_names.push_back(normalized_name);

  return attribute_index;
}

bool SymbolTable::declared_in_current_scope(
    const std::string &normalized_name) const {
  const std::vector<std::string> &declared_names{
      m_scope_stack.back().declared_names};

  return std::find(declared_names.begin(), declared_names.end(),
                   normalized_name) != declared_names.end();
}
