#include <iostream>
#include "lexer.h"
#include "ast/ast.h"

using namespace std;

int main()
{
  Lexer lexer("define x as 5;");
  vector<Token> tokens = lexer.getTokens();
  AST ast(tokens);

  return 0;
}