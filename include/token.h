#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <concepts>

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

  Token(TokenType tokenType, std::string tokenString) : tokenType(tokenType), tokenString(tokenString) {}
};

#endif