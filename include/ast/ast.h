#ifndef AST_H
#define AST_H

#include <concepts>
#include <stack>
#include <set>
#include <memory>
#include "ast/node.h"
#include "token.h"
#include "utils.h"

struct CodeBlock
{
  std::vector<Token> statement;
  std::vector<Token> bodyTokens;
};

class AST
{
private:
  std::vector<std::set<std::string>> scopes; // Stores the identifiers

  static std::variant<BinaryExpression, IntegerLiteral> evaluateExpression(const std::vector<Token> &statement);

  static std::shared_ptr<VariableStatement> evaluateVariableStatement(const std::vector<Token> &statement);

  std::shared_ptr<FunctionStatement> evaluateFunctionStatement(const CodeBlock &functionBlock);

  std::shared_ptr<IfStatement> evaluateIfStatement(const CodeBlock &ifBlock);

  std::shared_ptr<LoopStatement> evaluateLoopStatement(const CodeBlock &loopBlock);

  static std::vector<Token> extractBody(int &i, const std::vector<Token> &tokens);

  static void incrementToKeyword(int &i, const std::vector<Token> &tokens, std::vector<Token> &currentNodes, TokenType keyword);

public:
  AST() = default;

  std::shared_ptr<Root> constructAST(const std::vector<Token> &tokens);
};

#endif
