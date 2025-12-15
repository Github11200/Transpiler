#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <concepts>
#include <utility>
#include <vector>

enum class TokenType
{
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,

  LET,
  IF,
  BE,
  AS,
  POINT,
  DEFINE,
  REPEAT,
  TRUE,
  FALSE,
  WITH,

  SEMICOLON,
  OPENING_CURLY_BRACKET,
  CLOSING_CURLY_BRACKET,
  QUOTE,
  COMMA,
  SPACE,

  IDENTIFIER,
  INTEGER_LITERAL,
  FLOAT
};

class Token
{
public:
  TokenType tokenType;
  std::string tokenString;

  Token(const TokenType tokenType, std::string tokenString) : tokenType(tokenType), tokenString(std::move(tokenString)) {}
};

#endif