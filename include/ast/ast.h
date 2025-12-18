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

  static std::variant<BinaryExpression, IntegerLiteral> evaluateExpression(const std::vector<Token> &statement);

  static std::shared_ptr<VariableStatement> evaluateVariableStatement(const std::vector<Token> &statement);

  std::shared_ptr<FunctionStatement> evaluateFunctionStatement(const std::vector<Token> &statement);

  std::shared_ptr<IfStatement> evaluateIfStatement(const std::vector<Token> &statement);

  static std::vector<Token> extractCurlyBracesBody(int &i, const std::vector<Token> &tokens,
                                                   std::vector<Token> &currentNodes);

  static void incrementToOpeningCurlyBracket(int &i, const std::vector<Token> &tokens, std::vector<Token> &currentNodes);

public:
  AST() = default;

  std::shared_ptr<Root> constructAST(const std::vector<Token> &tokens);
};

#endif
