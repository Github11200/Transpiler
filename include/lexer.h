#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <set>
#include <algorithm>
#include <optional>
#include "token.h"
#include "utils.h"

class Lexer
{
private:
  std::set<std::string> keywords;
  std::set<std::string> operators;
  std::set<std::string> punctuator;
  std::string sourceCode;
  std::vector<std::string> splitSourceCode;
  int index;

public:
  explicit Lexer(std::string sourceCode);

  std::vector<Token> getTokens();
};

#endif