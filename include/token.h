#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType
{
  IDENTIFIER,
  KEYWORD,
  SEMICOLON,
  OPENING_CURLY_BRACKET,
  CLOSING_CURLY_BRACKET,
  QUOTE,
  OPERATOR,
  INTEGER_LITERAL,
  COMMA
};

class Token
{
private:
public:
  TokenType tokenType;
  std::string tokenString;

  Token(TokenType tokenType, std::string tokenString);
};

#endif