#ifndef AST_H
#define AST_H

#include <concepts>
#include <stack>
#include <set>
#include "ast/node.h"
#include "token.h"

class AST
{
private:
  std::vector<Token> tokens;
  std::vector<std::set<std::string>> scopes; // Stores the identifiers

  Expression evaluateExpression(std::vector<Token> &statement);
  VariableStatement evaluateVariableStatement(std::vector<Token> &statement);
  std::unique_ptr<ASTNode> evaluateStatement(std::vector<Token> &statement);

public:
  AST(std::vector<Token> tokens) : tokens(tokens) {}
  Root constructAST();
};

#endif