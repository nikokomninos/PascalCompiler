#pragma once

#include "token.hpp"
#include <vector>

class Scanner {
public:
  /**
   * @brief This class represents a scanner. It contains functions related
   * to scanning and tokenizing the stream
   *
   * @param &src A string containing the source code passed into the executable
   * as an argument. It is moved into member variable m_src
   */
  Scanner(const std::string &src);

  /**
   * @brief Scans through the given source stored in m_src and tokenizes it.
   * Achieved by going through each character in the stream, and determining
   * where a lexeme begins and ends, as well as its TokenType based on a given
   * set of rules:
   *
   * - TOK_OP if it is one character and is found within the
   *   operators set.
   * - TOK_WORD if the lexeme begins with a letter.
   * - TOK_NUMBER if the lexeme begins with a digit.
   * - TOK_UNKNOWN if the lexeme is of an unknown token type (currently).
   *
   * The tokenized stream is stored in member variable m_tokens.
   */
  void get_tokens();

  /**
   * @brief Prints the tokenized stream into a list of the following format:
   *
   * LEXEME : TOKENTYPE
   */
  void print_token_stream();

private:
  std::string m_src; // The original source stream
  std::vector<Token> m_tokens; // The scanned, tokenized stream

  /**
   * @brief A helper function that pushes the current lexeme to the 
   * token stream, if the lexeme string is not empty. Calls helper function
   * check_token_type to determine the TokenType of the lexeme
   *
   * @param &lexeme a reference to the current lexeme string
   *
   * @note Pre-condition: the lexeme is not an operator
   * @see check_token_type()
   */
  void push_lexeme(std::string &lexeme);

  /**
   * @brief A helper function that pushes an operator to the token stream.
   *
   * @param op the operator lexeme
   */
  void push_operator(char op);

  /**
   * @brief A helper function that determines the token type of a lexeme
   *
   * @param &lexeme a reference to the current lexeme string
   */
  TokenType check_token_type(const std::string &lexeme);
};
