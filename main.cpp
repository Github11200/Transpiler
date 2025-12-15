#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "ast/ast.h"

using namespace std;

int main()
{
  string filePath = "../code.txt";
  ifstream file(filePath);

  if (!file.is_open())
  {
    cout << "Couldn't open file." << endl;
    return -1;
  }

  string line;
  string code;

  while (getline(file, line))
    code += line;

  Lexer lexer(code);
  vector<Token> tokens = lexer.getTokens();
  AST ast;

  shared_ptr<Root> node = ast.constructAST(tokens);
  Root *pointer = node.get();
  ASTNode *inty = pointer->nodes[0].get();
  for (auto node : pointer->nodes)
    node->readValue();

  file.close();

  return 0;
}