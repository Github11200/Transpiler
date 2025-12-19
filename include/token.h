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
  TIMES,
  DIVIDE,

  LET,
  BE,
  POINTER,
  TO,
  STOP,
  DEFINE,
  AS,
  END,
  WITH,
  IF,
  GREATER,
  THAN,
  THEN,
  LESS,
  OR,
  EQUAL,
  OTHERWISE,
  FOR,
  REPEAT,

  IDENTIFIER,
  INTEGER_LITERAL
};

class Token
{
public:
  TokenType tokenType;
  std::string tokenString;

  Token(const TokenType tokenType, std::string tokenString) : tokenType(tokenType), tokenString(std::move(tokenString)) {}
};

#endif