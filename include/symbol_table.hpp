#pragma once

#include "token.hpp"
#include <array>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

enum class SymbolType { Keyword, Operator, Program, Variable, Procedure };

enum class DataType { Unknown, None, Integer, Real };

struct PredefinedSymbol {
  std::string lexeme;
  TokenType token_type;
  SymbolType symbol_type;
  DataType data_type;
};

inline constexpr std::array<PredefinedSymbol, 34> predefined_symbols{{
    {"PROGRAM", TokenType::TOK_PROGRAM, SymbolType::Keyword, DataType::None},
    {"PROCEDURE", TokenType::TOK_PROCEDURE, SymbolType::Keyword,
     DataType::None},
    {"VAR", TokenType::TOK_VAR, SymbolType::Keyword, DataType::None},
    {"BEGIN", TokenType::TOK_BEGIN, SymbolType::Keyword, DataType::None},
    {"END", TokenType::TOK_END, SymbolType::Keyword, DataType::None},
    {"IF", TokenType::TOK_IF, SymbolType::Keyword, DataType::None},
    {"THEN", TokenType::TOK_THEN, SymbolType::Keyword, DataType::None},
    {"ELSE", TokenType::TOK_ELSE, SymbolType::Keyword, DataType::None},
    {"WHILE", TokenType::TOK_WHILE, SymbolType::Keyword, DataType::None},
    {"DO", TokenType::TOK_DO, SymbolType::Keyword, DataType::None},
    {"INTEGER", TokenType::TOK_INTEGER, SymbolType::Keyword, DataType::None},
    {"REAL", TokenType::TOK_REAL, SymbolType::Keyword, DataType::None},
    {"=", TokenType::TOK_EQUAL, SymbolType::Operator, DataType::None},
    {">", TokenType::TOK_GREATER, SymbolType::Operator, DataType::None},
    {"<", TokenType::TOK_LESS, SymbolType::Operator, DataType::None},
    {">=", TokenType::TOK_GREATER_EQUAL, SymbolType::Operator, DataType::None},
    {"<=", TokenType::TOK_LESS_EQUAL, SymbolType::Operator, DataType::None},
    {"<>", TokenType::TOK_NOT_EQUAL, SymbolType::Operator, DataType::None},
    {"NOT", TokenType::TOK_NOT, SymbolType::Operator, DataType::None},
    {"+", TokenType::TOK_PLUS, SymbolType::Operator, DataType::None},
    {"-", TokenType::TOK_MINUS, SymbolType::Operator, DataType::None},
    {"OR", TokenType::TOK_OR, SymbolType::Operator, DataType::None},
    {"*", TokenType::TOK_MULTIPLY, SymbolType::Operator, DataType::None},
    {"/", TokenType::TOK_DIVIDE, SymbolType::Operator, DataType::None},
    {"DIV", TokenType::TOK_DIV, SymbolType::Operator, DataType::None},
    {"MOD", TokenType::TOK_MOD, SymbolType::Operator, DataType::None},
    {"AND", TokenType::TOK_AND, SymbolType::Operator, DataType::None},
    {":=", TokenType::TOK_ASSIGN, SymbolType::Operator, DataType::None},
    {"(", TokenType::TOK_LEFT_PAREN, SymbolType::Operator, DataType::None},
    {")", TokenType::TOK_RIGHT_PAREN, SymbolType::Operator, DataType::None},
    {",", TokenType::TOK_COMMA, SymbolType::Operator, DataType::None},
    {";", TokenType::TOK_SEMICOLON, SymbolType::Operator, DataType::None},
    {":", TokenType::TOK_COLON, SymbolType::Operator, DataType::None},
    {".", TokenType::TOK_PERIOD, SymbolType::Operator, DataType::None},
}};

struct NameEntry {
  std::optional<std::size_t> current_attribute_index;
};

struct AttributeEntry {
  TokenType token_type;
  SymbolType symbol_type;
  DataType data_type;
  std::optional<std::size_t> outer_attribute_index;
};

struct Scope {
  std::vector<std::string> declared_names;
};

class SymbolTable {
public:
  SymbolTable();
  bool declare(const std::string &name, SymbolType symbol_type,
               DataType data_type,
               TokenType token_type = TokenType::TOK_IDENTIFIER);

  std::optional<std::size_t> lookup(const std::string &name) const;

  std::optional<TokenType>
  lookup_predefined_token(const std::string &lexeme) const;

  const AttributeEntry &get_attribute(std::size_t attribute_index) const;

  void enter_scope();
  void exit_scope();

private:
  std::unordered_map<std::string, NameEntry> m_name_table;
  std::vector<AttributeEntry> m_attribute_table;
  std::vector<Scope> m_scope_stack;


  static std::string normalize_name(const std::string& name);

  NameEntry &install_name(const std::string &name);

  std::size_t install_attribute(const std::string &name, SymbolType symbol_type,
                                DataType data_type, TokenType token_type);

  bool declared_in_current_scope(const std::string &normalized_name) const;
};
