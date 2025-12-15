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

  void readValue() override { std::cout << value; }
};

struct BinaryExpression : ASTNode
{
  TokenType operatorType;
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

    std::visit([&](const auto &var)
               {  if constexpr (std::is_same_v<std::decay_t<decltype(var)>, BinaryExpression>)
                    this->right = std::make_shared<BinaryExpression>(var);
                  if constexpr (std::is_same_v<std::decay_t<decltype(var)>, IntegerLiteral>)
                    this->right = std::make_shared<IntegerLiteral>(var); }, right);
  }

  void readValue() override
  {
    if (std::holds_alternative<std::shared_ptr<IntegerLiteral>>(left))
      std::get<std::shared_ptr<IntegerLiteral>>(left)->readValue();
    else if (std::holds_alternative<std::shared_ptr<BinaryExpression>>(left))
      std::get<std::shared_ptr<BinaryExpression>>(left)->readValue();

    switch (operatorType)
    {
    case TokenType::PLUS:
      std::cout << " + ";
      break;
    case TokenType::MINUS:
      std::cout << " - ";
      break;
    case TokenType::MULTIPLY:
      std::cout << " * ";
      break;
    case TokenType::DIVIDE:
      std::cout << " / ";
      break;

    default:
      break;
    }

    if (std::holds_alternative<std::shared_ptr<IntegerLiteral>>(right))
      std::get<std::shared_ptr<IntegerLiteral>>(right)
          ->readValue();
    else if (std::holds_alternative<std::shared_ptr<BinaryExpression>>(right))
      std::get<std::shared_ptr<BinaryExpression>>(right)
          ->readValue();
  }
};

struct VariableStatement : ASTNode
{
  std::string identifier;
  std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<IntegerLiteral>> value;

  VariableStatement(std::string identifier, std::variant<BinaryExpression, IntegerLiteral> value)
  {
    this->identifier = identifier;
    std::visit([&](const auto &var)
               { if constexpr (std::is_same_v<std::decay_t<decltype(var)>, BinaryExpression>)
                    this->value = std::make_shared<BinaryExpression>(var);
                  if constexpr (std::is_same_v<std::decay_t<decltype(var)>, IntegerLiteral>)
                    this->value = std::make_shared<IntegerLiteral>(var); }, value);
  }

  void readValue() override
  {
    std::cout << this->identifier << ": ";
    if (std::holds_alternative<std::shared_ptr<IntegerLiteral>>(value))
      std::get<std::shared_ptr<IntegerLiteral>>(value)->readValue();
    else if (std::holds_alternative<std::shared_ptr<BinaryExpression>>(value))
      std::get<std::shared_ptr<BinaryExpression>>(value)->readValue();
    std::cout << std::endl;
  }
};

struct FunctionStatement : ASTNode
{
  std::string identifier;
  std::vector<std::string> parameters;
  std::vector<std::shared_ptr<ASTNode>> body;

  FunctionStatement(std::string identifier, std::vector<std::shared_ptr<ASTNode>> body, std::vector<std::string> parameters)
  {
    this->identifier = identifier;
    if (parameters.size() > 0)
      this->parameters = parameters;
    this->body = body;
  }

  void readValue() override
  {
    for (auto node : body)
      node.get()->readValue();
  }
};

#endif