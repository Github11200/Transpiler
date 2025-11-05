#ifndef NODE_H
#define NODE_H

#include <string>
#include <variant>
#include "token.h"

class ASTNode
{
public:
  virtual void visit();
};

class Expression : ASTNode
{
public:
  TokenType operatorType;
  std::variant<Expression, int, double> left;
  std::variant<Expression, int, double> right;
};

class VariableStatement : ASTNode
{
public:
  std::string identifier;
  Expression &expression;

  VariableStatement(std::string identifier, Expression &expression)
  {
    this->identifier = identifier;
    this->expression = expression;
  }
};

#endif