#ifndef NODE_H
#define NODE_H

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <optional>
#include <iostream>
#include "token.h"

struct ASTNode
{
  virtual void readValue() = 0;
};

struct Root : ASTNode
{
  std::vector<ASTNode> nodes;
};

struct IntegerLiteral : ASTNode
{
  int value;
  IntegerLiteral(int value) : value(value) {}

  void readValue() override { std::cout << value << std::endl; }
};

struct BinaryExpression : ASTNode
{
  std::optional<TokenType> operatorType;
  std::variant<BinaryExpression *, IntegerLiteral *> left;
  std::variant<BinaryExpression *, IntegerLiteral *> right;

  BinaryExpression(TokenType operatorType, std::variant<BinaryExpression *, IntegerLiteral *> left,
                   std::variant<BinaryExpression *,
                                IntegerLiteral *>
                       right) : operatorType(operatorType),
                                left(left),
                                right(right) {}

  void readValue() override { std::cout << "hi" << std::endl; }
};

struct VariableStatement : ASTNode
{
  std::string identifier;
  std::variant<BinaryExpression *, IntegerLiteral *> value;

  VariableStatement(std::string identifier, std::variant<BinaryExpression *, IntegerLiteral *> value) : identifier(identifier),
                                                                                                        value(value) {}

  void readValue() override { std::cout << "hi" << std::endl; }
};

#endif