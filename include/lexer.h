#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <set>
#include <algorithm>
#include "token.h"

class Lexer
{
private:
  set<string> keywords;
  set<string> operators;
  set<string> punctuator;
  std::string sourceCode;
  int index;

  char peekCharacter();
  char consumeCharacter();

  std::string peekWord();
  std::string consumeWord();

public:
  Lexer(std::string sourceCode);
  vector<Token> getTokens();
};

#endif