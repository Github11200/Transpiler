#include "ast/ast.h"

using namespace std;

variant<BinaryExpression, IntegerLiteral> AST::evaluateExpression(vector<Token> &statement)
{
  // The statement is something like let x be 5;
  if (statement.size() == 1)
    return IntegerLiteral(stoi(statement[0].tokenString));

  // We will assume it contains an operator otherwise
  BinaryExpression *binaryExpression = nullptr;
  for (int i = 0; i < statement.size(); ++i)
  {
    if (!isOperator(statement[i].tokenType))
      continue;

    if (i + 1 == statement.size())
      throw "An operand must be added after the operator.";

    IntegerLiteral *leftInteger = new IntegerLiteral(stoi(statement[i - 1].tokenString));
    IntegerLiteral *rightInteger = new IntegerLiteral(stoi(statement[i + 1].tokenString));
    BinaryExpression newExpression(statement[i].tokenType, leftInteger, rightInteger);

    // If there's already an expression then this should go to it's right
    if (binaryExpression != nullptr)
      binaryExpression->right = &newExpression;
    else
      binaryExpression = &newExpression;
  }

  return *binaryExpression;
}

VariableStatement AST::evaluateVariableStatement(vector<Token> &statement)
{
  string identifier = statement[1].tokenString;

  vector<Token> expressionTokens;
  for (int i = 3; i < statement.size() - 1; ++i)
    expressionTokens.push_back(statement[i]);

  variant<BinaryExpression, IntegerLiteral> expression = evaluateExpression(expressionTokens);
  if (holds_alternative<IntegerLiteral>(expression))
    return VariableStatement(identifier, &get<IntegerLiteral>(expression));
  // return VariableStatement(identifier, expression);
}

ASTNode AST::evaluateStatement(vector<Token> &statement)
{
  /*
  This is a variable statement: let x be 5;
                                ^^^   ^^
                                We're looking for these keywords
  */
  if (statement[0].tokenType == TokenType::LET && statement[2].tokenType == TokenType::BE)
    return evaluateVariableStatement(statement);
  /*
  This is a function statement: define x as {}
                                ^^^^^^   ^^
                                We're looking for these keywords
  */
  else if (statement[0].tokenType == TokenType::DEFINE && statement[2].tokenType == TokenType::AS)
  {
  }
}

Root AST::constructAST()
{
  Root rootNode;

  vector<Token> currentStatement;
  for (int i = 0; i < tokens.size(); ++i)
  {
    currentStatement.push_back(tokens[i]);
  }
  ASTNode node = evaluateStatement(currentStatement);
  rootNode.nodes.push_back(evaluateStatement(currentStatement));

  return rootNode;
}