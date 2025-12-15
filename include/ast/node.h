#ifndef NODE_H
#define NODE_H

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <iostream>
#include "token.h"

struct ASTNode {
  virtual ~ASTNode() = default;

  virtual void readValue() = 0;
};

struct Root final : ASTNode {
  std::vector<std::shared_ptr<ASTNode> > nodes;

  void readValue() override;
};

struct IntegerLiteral final : ASTNode {
  int value;

  explicit IntegerLiteral(const int value) : value(value) {
  }

  void readValue() override;
};

struct BinaryExpression final : ASTNode {
  TokenType operatorType;
  std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<IntegerLiteral> > left;
  std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<IntegerLiteral> > right;

  BinaryExpression(TokenType operatorType, std::variant<BinaryExpression, IntegerLiteral> left,
                   std::variant<BinaryExpression,
                     IntegerLiteral>
                   right);

  void readValue() override;
};

struct VariableStatement final : ASTNode {
  std::string identifier;
  std::variant<std::shared_ptr<BinaryExpression>, std::shared_ptr<IntegerLiteral> > value;

  VariableStatement(const std::string &identifier, std::variant<BinaryExpression, IntegerLiteral> value);

  void readValue() override;
};

struct FunctionStatement final : ASTNode {
  std::string identifier;
  std::vector<std::string> parameters;
  std::vector<std::shared_ptr<ASTNode> > body;

  FunctionStatement(const std::string &identifier, const std::vector<std::shared_ptr<ASTNode> > &body,
                    const std::vector<std::string> &parameters);

  void readValue() override;
};

struct IfStatement final : ASTNode {
  std::shared_ptr<ASTNode> condition;
  std::vector<std::shared_ptr<ASTNode> > body;

  IfStatement(const std::shared_ptr<ASTNode> &condition, const std::vector<std::shared_ptr<ASTNode> > &body);

  void readValue() override;
};

#endif
