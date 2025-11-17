#ifndef NODE_H
#define NODE_H

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <optional>
#include "token.h"

#define EXPRESSION_TYPES BinaryExpression, IntegerLiteral
#define VARIABLE_VARIANT std::variant<std::unique_ptr<BinaryExpression>, std::unique_ptr<IntegerLiteral>, int>

struct ASTNode
{
};

struct Root : ASTNode
{
  std::vector<std::unique_ptr<ASTNode>> nodes;
};

struct BinaryExpression : ASTNode
{
  std::optional<TokenType> operatorType;
  std::variant<EXPRESSION_TYPES> left;
  std::variant<EXPRESSION_TYPES> right;

  BinaryExpression(TokenType operatorType, std::variant<EXPRESSION_TYPES> left, std::variant<EXPRESSION_TYPES> right) : operatorType(operatorType),
                                                                                                                        left(left),
                                                                                                                        right(right) {}
};

struct IntegerLiteral : ASTNode
{
  int value;
  IntegerLiteral(int value) : value(value) {}
};

struct VariableStatement : ASTNode
{
  std::string identifier;
  VARIABLE_VARIANT value;

  VariableStatement(std::string identifier, VARIABLE_VARIANT value)
  {
    this->identifier = identifier;

    if (std::holds_alternative<std::unique_ptr<BinaryExpression>>(value))
      this->value = std::make_unique<BinaryExpression>(value);
    else if (std::holds_alternative<std::unique_ptr<IntegerLiteral>>(value))
      this->value = std::make_unique<IntegerLiteral>(value);
    else
      this->value.emplace<int>(std::get<int>(value));
  }
};

#endif