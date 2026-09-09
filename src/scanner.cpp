#include "scanner.hpp"
#include "token.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iomanip>
#include <iostream>

Scanner::Scanner(const std::string &src) { m_src = std::move(src); }

void Scanner::get_tokens() {
  std::string lexeme{};
  std::size_t line_number{1}; // For future use

  // Lambda function to look a character ahead without going out
  // of bounds
  auto look_ahead = [this](std::size_t index) -> char {
    return index + 1 < m_src.size() ? m_src.at(index + 1) : '\0';
  };

  for (std::size_t i = 0; i < m_src.size(); ++i) {
    const char c = m_src.at(i);

    if (c == '\n')
      ++line_number;

    if (std::isspace(c)) {
      push_lexeme(lexeme);
      continue;
    }

    if (std::isalnum(c)) {
      lexeme.push_back(c);
      continue;
    }

    // A decimal point belongs to a number only when followed by a digit
    if (c == '.' && !lexeme.empty() &&
        std::all_of(lexeme.begin(), lexeme.end(),
                    [](unsigned char digit) { return std::isdigit(digit); }) &&
        std::isdigit(look_ahead(i))) {
      lexeme.push_back(c);
      continue;
    }

    // Symbols end the preceding lexeme and are pushed as their own tokens
    push_lexeme(lexeme);
    std::string symbol{c};
    const char next = look_ahead(i);
    if ((c == ':' && next == '=') ||
        (c == '<' && (next == '=' || next == '>')) ||
        (c == '>' && next == '=')) {
      symbol.push_back(next);
      ++i;
    }
    m_tokens.emplace_back(symbol, check_token_type(symbol));
  }

  push_lexeme(lexeme);
}

void Scanner::push_lexeme(std::string &lexeme) {
  if (!lexeme.empty()) {
    m_tokens.emplace_back(lexeme, check_token_type(lexeme));
    lexeme.clear();
  }
}

void Scanner::print_token_stream() {
  for (const Token &t : m_tokens) {
    std::cout << std::left << std::setw(15) << t.lexeme << " : "
              << token_type_names.at(static_cast<size_t>(t.type)) << "\n";
  }
}

TokenType Scanner::check_token_type(const std::string &lexeme) {
  std::string upper_lexeme{lexeme};
  std::transform(upper_lexeme.begin(), upper_lexeme.end(), upper_lexeme.begin(),
                 [](unsigned char c) { return std::toupper(c); });

  if (special_tokens.contains(upper_lexeme))
    return special_tokens.at(upper_lexeme);

  if (!lexeme.empty() &&
      std::all_of(lexeme.begin(), lexeme.end(),
                  [](unsigned char c) { return std::isdigit(c) || c == '.'; }))
    return TokenType::TOK_NUMBER;

  if (!lexeme.empty() && std::isalpha(lexeme.at(0)) &&
      std::all_of(lexeme.begin() + 1, lexeme.end(),
                  [](unsigned char c) { return std::isalnum(c); }))
    return TokenType::TOK_IDENTIFIER;

  return TokenType::TOK_WORD;
}
