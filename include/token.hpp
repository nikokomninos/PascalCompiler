#pragma once

#include <array>
#include <string>
#include <unordered_map>

enum class TokenType {
  // Keywords
  TOK_PROGRAM,
  TOK_PROCEDURE,
  TOK_VAR,
  TOK_BEGIN,
  TOK_END,
  TOK_IF,
  TOK_THEN,
  TOK_ELSE,
  TOK_WHILE,
  TOK_DO,

  // Data Types
  TOK_INTEGER,
  TOK_REAL,

  // Rel ops
  TOK_EQUAL,         // =
  TOK_GREATER,       // >
  TOK_LESS,          // <
  TOK_GREATER_EQUAL, // >=
  TOK_LESS_EQUAL,    // <=
  TOK_NOT_EQUAL,     // <>
  TOK_NOT,

  // Add ops
  TOK_PLUS, // +
  TOK_MINUS, // -
  TOK_OR,

  // Mul ops
  TOK_MULTIPLY, // *
  TOK_DIVIDE, // /
  TOK_DIV,
  TOK_MOD,
  TOK_AND,

  // Assign ops
  TOK_ASSIGN, // :=

  // Symbol types
  TOK_IDENTIFIER,
  TOK_NUMBER,

  // Separating operators
  TOK_LEFT_PAREN, // (
  TOK_RIGHT_PAREN, // )
  TOK_COMMA, // ,
  TOK_SEMICOLON, // ;
  TOK_COLON, // :
  TOK_PERIOD, // .

  // Extra token types
  TOK_WORD,
};

const std::unordered_map<std::string, TokenType> special_tokens{
    {"PROGRAM", TokenType::TOK_PROGRAM},
    {"PROCEDURE", TokenType::TOK_PROCEDURE},
    {"VAR", TokenType::TOK_VAR},
    {"BEGIN", TokenType::TOK_BEGIN},
    {"END", TokenType::TOK_END},
    {"IF", TokenType::TOK_IF},
    {"THEN", TokenType::TOK_THEN},
    {"ELSE", TokenType::TOK_ELSE},
    {"WHILE", TokenType::TOK_WHILE},
    {"DO", TokenType::TOK_DO},
    {"INTEGER", TokenType::TOK_INTEGER},
    {"REAL", TokenType::TOK_REAL},
    {"CONST", TokenType::TOK_WORD},
    {"=", TokenType::TOK_EQUAL},
    {">", TokenType::TOK_GREATER},
    {"<", TokenType::TOK_LESS},
    {">=", TokenType::TOK_GREATER_EQUAL},
    {"<=", TokenType::TOK_LESS_EQUAL},
    {"<>", TokenType::TOK_NOT_EQUAL},
    {"NOT", TokenType::TOK_NOT},
    {"+", TokenType::TOK_PLUS},
    {"-", TokenType::TOK_MINUS},
    {"OR", TokenType::TOK_OR},
    {"*", TokenType::TOK_MULTIPLY},
    {"/", TokenType::TOK_DIVIDE},
    {"DIV", TokenType::TOK_DIV},
    {"MOD", TokenType::TOK_MOD},
    {"AND", TokenType::TOK_AND},
    {":=", TokenType::TOK_ASSIGN},
    {"(", TokenType::TOK_LEFT_PAREN},
    {")", TokenType::TOK_RIGHT_PAREN},
    {",", TokenType::TOK_COMMA},
    {";", TokenType::TOK_SEMICOLON},
    {":", TokenType::TOK_COLON},
    {".", TokenType::TOK_PERIOD},
};

// Lookup table for printing token type names (since enum names cannot
// be printed)
inline constexpr std::array<std::string, 37> token_type_names{
    "TOK_PROGRAM",    "TOK_PROCEDURE", "TOK_VAR",        "TOK_BEGIN",
    "TOK_END",        "TOK_IF",        "TOK_THEN",       "TOK_ELSE",
    "TOK_WHILE",      "TOK_DO",        "TOK_INTEGER",    "TOK_REAL",
    "TOK_EQUAL",      "TOK_GREATER",   "TOK_LESS",       "TOK_GREATER_EQUAL",
    "TOK_LESS_EQUAL", "TOK_NOT_EQUAL", "TOK_NOT",        "TOK_PLUS",
    "TOK_MINUS",      "TOK_OR",        "TOK_MULTIPLY",   "TOK_DIVIDE",
    "TOK_DIV",        "TOK_MOD",       "TOK_AND",        "TOK_ASSIGN",
    "TOK_IDENTIFIER", "TOK_NUMBER",    "TOK_LEFT_PAREN", "TOK_RIGHT_PAREN",
    "TOK_COMMA",      "TOK_SEMICOLON", "TOK_COLON",      "TOK_PERIOD",
    "TOK_WORD",
};

struct Token {
  const std::string lexeme;
  const TokenType type;
};
