#ifndef AST_H
#define AST_H

#include <concepts>
#include <stack>
#include <set>
#include <memory>
#include "ast/node.h"
#include "token.h"
#include "utils.h"

class AST
{
private:
  std::vector<std::set<std::string>> scopes; // Stores the identifiers

  std::variant<BinaryExpression, IntegerLiteral> evaluateExpression(std::vector<Token> &statement);
  std::shared_ptr<VariableStatement> evaluateVariableStatement(std::vector<Token> &statement);
  std::shared_ptr<FunctionStatement> evaluateFunctionStatement(std::vector<Token> &tokens);

public:
  AST() {}
  std::shared_ptr<Root> constructAST(std::vector<Token> tokens);
};

#endif