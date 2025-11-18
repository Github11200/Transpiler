#ifndef NODE_H
#define NODE_H

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <optional>
#include "token.h"

struct ASTNode
{
};

struct Root : ASTNode
{
  std::vector<std::unique_ptr<ASTNode>> nodes;
};

struct IntegerLiteral : ASTNode
{
  int value;
  IntegerLiteral(int value) : value(value) {}
  IntegerLiteral() = default;
};

struct BinaryExpression : ASTNode
{
  std::optional<TokenType> operatorType;
  std::variant<BinaryExpression *, IntegerLiteral> left;
  std::variant<BinaryExpression *, IntegerLiteral> right;

  BinaryExpression(TokenType operatorType, IntegerLiteral left, IntegerLiteral right) : operatorType(operatorType),
                                                                                        left(left),
                                                                                        right(right) {}

  BinaryExpression(TokenType operatorType, BinaryExpression *left, BinaryExpression *right) : operatorType(operatorType),
                                                                                              left(left),
                                                                                              right(right) {}

  BinaryExpression() = default;
};

struct VariableStatement : ASTNode
{
  std::string identifier;
  std::variant<BinaryExpression, IntegerLiteral> value;

  VariableStatement(std::string identifier, std::variant<BinaryExpression, IntegerLiteral> value) : identifier(identifier),
                                                                                                    value(value) {}
};

#endif