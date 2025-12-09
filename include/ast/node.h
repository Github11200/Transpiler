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
  std::vector<std::shared_ptr<ASTNode>> nodes;

  void readValue() override { std::cout << "hi" << std::endl; }
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
  std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<IntegerLiteral>> left;
  std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<IntegerLiteral>> right;

  BinaryExpression(TokenType operatorType, std::variant<BinaryExpression, IntegerLiteral> left,
                   std::variant<BinaryExpression,
                                IntegerLiteral>
                       right)
  {
    this->operatorType = operatorType;
    std::visit([&](const auto &var)
               {  if constexpr (std::is_same_v<std::decay_t<decltype(var)>, BinaryExpression>)
                    this->left = std::make_shared<BinaryExpression>(var);
                  if constexpr (std::is_same_v<std::decay_t<decltype(var)>, IntegerLiteral>)
                    this->left = std::make_shared<IntegerLiteral>(var); }, left);
  }

  void readValue() override { std::cout << "hi" << std::endl; }
};

struct VariableStatement : ASTNode
{
  std::string identifier;
  std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<IntegerLiteral>> value;

  VariableStatement(std::string identifier, std::variant<BinaryExpression, IntegerLiteral> value)
  {
    std::visit([&](const auto &var)
               { if constexpr (std::is_same_v<std::decay_t<decltype(var)>, BinaryExpression>)
                    this->value = std::make_shared<BinaryExpression>(var);
                  if constexpr (std::is_same_v<std::decay_t<decltype(var)>, IntegerLiteral>)
                    this->value = std::make_shared<IntegerLiteral>(var); }, value);
  }

  void readValue() override
  {
    if (std::holds_alternative<std::shared_ptr<IntegerLiteral>>(value))
      std::get<std::shared_ptr<IntegerLiteral>>(value)->readValue();
  }
};

#endif