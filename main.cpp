#include <iostream>
#include <memory>
#include "lexer.h"
#include "ast/ast.h"

using namespace std;

int main()
{
  Lexer lexer("let x be 1000000000;");
  vector<Token> tokens = lexer.getTokens();
  AST ast(tokens);

  shared_ptr<Root> node = ast.constructAST();
  Root *pointer = node.get();
  ASTNode *inty = pointer->nodes[0].get();

  return 0;
}