#include <iostream>
#include "lexer.h"
#include "ast/ast.h"

using namespace std;

int main()
{
  Lexer lexer("let x be 5;");
  vector<Token> tokens = lexer.getTokens();
  AST ast(tokens);

  ast.constructAST();
  return 0;
}