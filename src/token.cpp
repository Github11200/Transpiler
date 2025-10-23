#include "token.h"

using namespace std;

Token::Token(TokenType tokenType, string tokenString)
{
  this->tokenType = tokenType;
  this->tokenString = tokenString;
}