#include "ast/ast.h"

using namespace std;

variant<BinaryExpression, IntegerLiteral> AST::evaluateExpression(vector<Token> &statement)
{
  // The statement is something like let x be 5;
  if (statement.size() == 1)
    return IntegerLiteral(stoi(statement[0].tokenString));

  // We will assume it contains an operator otherwise
  unique_ptr<BinaryExpression> binaryExpression = nullptr;
  for (int i = 0; i < statement.size(); ++i)
  {
    if (!isOperator(statement[i].tokenType))
      continue;

    if (i + 1 == statement.size())
      throw "An operand must be added after the operator.";

    IntegerLiteral leftInteger(stoi(statement[i - 1].tokenString));
    IntegerLiteral rightInteger(stoi(statement[i + 1].tokenString));
    BinaryExpression newExpression(statement[i].tokenType, leftInteger, rightInteger);

    // If there's already an expression then this should go to it's right
    if (binaryExpression != nullptr)
      binaryExpression->right = std::make_shared<BinaryExpression>(newExpression);
    else
      binaryExpression = make_unique<BinaryExpression>(newExpression);
  }

  return *binaryExpression.get();
}

shared_ptr<VariableStatement> AST::evaluateVariableStatement(vector<Token> &statement)
{
  string identifier = statement[1].tokenString;

  vector<Token> expressionTokens;
  for (int i = 3; i < statement.size() - 1; ++i)
    expressionTokens.push_back(statement[i]);

  variant<BinaryExpression, IntegerLiteral> expression = evaluateExpression(expressionTokens);
  return make_shared<VariableStatement>(identifier, expression);
}

shared_ptr<FunctionStatement> AST::evaluateFunctionStatement(vector<Token> &statement)
{
  string identifier = statement[1].tokenString;
  vector<string> parameters;

  // This is where the opening curly bracket is
  int startOfFunctionBody = 3;

  // The function has parameters
  if (statement[2].tokenType == TokenType::WITH)
  {
    int i = 3;
    for (; i < statement.size(); ++i)
    {
      if (statement[i].tokenType == TokenType::COMMA)
        continue;
      else if (statement[i].tokenType == TokenType::AS)
        break;
      parameters.push_back(statement[i].tokenString);
    }
    startOfFunctionBody = i + 1;
  }

  vector<Token> functionBodyTokens;

  // Subtract 1 to exclude closing bracket
  for (int i = startOfFunctionBody + 1; i < statement.size(); ++i)
    functionBodyTokens.push_back(statement[i]);

  vector<shared_ptr<ASTNode>> functionBody = constructAST(functionBodyTokens).get()->nodes;
  return make_shared<FunctionStatement>(identifier, functionBody, parameters);
}

shared_ptr<Root> AST::constructAST(vector<Token> tokens)
{
  Root rootNode;

  vector<Token> currentNodes;
  for (int i = 0; i < tokens.size(); ++i)
  {
    currentNodes.push_back(tokens[i]);
    std::shared_ptr<ASTNode> newNode = nullptr;

    if (tokens[i].tokenType == TokenType::SEMICOLON)
    {
      newNode = evaluateVariableStatement(currentNodes);
      currentNodes.clear();
    }
    else if (tokens[i].tokenType == TokenType::OPENING_CURLY_BRACKET)
    {
      int bracketsDepth = 0;
      ++i;
      for (; i < tokens.size(); ++i)
      {
        if (tokens[i].tokenType == TokenType::CLOSING_CURLY_BRACKET && bracketsDepth == 0)
          break;
        else if (tokens[i].tokenType == TokenType::OPENING_CURLY_BRACKET)
          ++bracketsDepth;
        currentNodes.push_back(tokens[i]);
      }
      newNode = evaluateFunctionStatement(currentNodes);
    }

    if (newNode != nullptr)
      rootNode.nodes.push_back(newNode);
  }

  return make_shared<Root>(rootNode);
}