#ifndef NODE_H
#define NODE_H

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include "token.h"

#define EXPRESSION_TYPES std::shared_ptr<Expression>, int, double

struct ASTNode
{
};

struct Root : ASTNode
{
  std::vector<std::unique_ptr<ASTNode>> nodes;
};

struct Expression : ASTNode
{
  TokenType operatorType;
  std::variant<EXPRESSION_TYPES> left;
  std::variant<EXPRESSION_TYPES> right;

  Expression(TokenType operatorType, std::variant<EXPRESSION_TYPES> left, std::variant<EXPRESSION_TYPES> right) : operatorType(operatorType),
                                                                                                                  left(left),
                                                                                                                  right(right) {}
};

struct VariableStatement : ASTNode
{
  std::string identifier;
  std::unique_ptr<Expression> expression;

  VariableStatement(std::string identifier, Expression expression)
  {
    this->identifier = identifier;
    this->expression = std::make_unique<Expression>(expression);
  }
};

#endif