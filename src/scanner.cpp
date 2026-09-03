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

  for (const char &c : m_src) {
    if (c == '\n') {
      ++line_number;
    }

    // Explicitly checks if the lexeme is a one-character operator, since
    // operators are special and act as a clear split between lexemes.
    // If the lexeme is an operator, it pushes the current lexeme to the stream,
    // then pushes the operator lexeme to the stream.
    if (std::find(operators.begin(), operators.end(), c) != operators.end()) {
      push_lexeme(lexeme);
      push_operator(c);
      continue;
    }

    // Pushes the current lexeme if whitespace is encountered.
    if (std::isspace(c)) {
      push_lexeme(lexeme);
      continue;
    }

    lexeme.push_back(c);
  }

  // Pushes the final lexeme at the end of the loop
  push_lexeme(lexeme);
}

void Scanner::push_lexeme(std::string &lexeme) {
  if (!lexeme.empty()) {
    m_tokens.push_back(Token(lexeme, check_token_type(lexeme)));
    lexeme.clear();
  }
}

void Scanner::push_operator(char op) {
  m_tokens.push_back(Token(std::string{op}, TokenType::TOK_OP));
}

void Scanner::print_token_stream() {
  for (const Token &t : m_tokens) {
    std::cout << std::left << std::setw(15) << t.lexeme << " : "
              << token_type_names.at(static_cast<size_t>(t.type)) << "\n";
  }
}

TokenType Scanner::check_token_type(const std::string &lexeme) {
  if (isalpha(lexeme.at(0)))
    return TokenType::TOK_WORD;
  else if (isnumber(lexeme.at(0)))
    return TokenType::TOK_NUMBER;

  return TokenType::TOK_UNKNOWN;
}
