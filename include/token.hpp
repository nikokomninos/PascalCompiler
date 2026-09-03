#pragma once

#include <array>
#include <string>

// Set of predefined operator lexemes
inline constexpr std::array<char, 5> operators{'(', ')', ',', ';', '='};

enum class TokenType { TOK_WORD, TOK_NUMBER, TOK_OP, TOK_UNKNOWN };

// Lookup table for printing token type names (since enum names cannot
// be printed)
inline constexpr std::array<std::string, 4> token_type_names {
  "TOK_WORD",
  "TOK_NUMBER",
  "TOK_OP",
  "TOK_UNKNOWN"
};

struct Token {
  std::string lexeme;
  TokenType type;
};
