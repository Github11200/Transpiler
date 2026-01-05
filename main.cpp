#include "ast/ast.h"
#include "lexer.h"
#include "codeGenerator.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

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

  shared_ptr<Root> rootNode = ast.constructAST(tokens);
  CodeGenerator codeGenerator(rootNode);

  codeGenerator.generate("compiled.cpp");
  file.close();

  return 0;
}
