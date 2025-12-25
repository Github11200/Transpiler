#include "ast/ast.h"

using namespace std;

vector<Token> AST::extractBody(int &i, const vector<Token> &tokens,
                               vector<Token> &currentNodes)
{
  int depth = 0;
  for (; i < tokens.size(); ++i)
  {
    if (tokens[i].tokenType == TokenType::END && depth == 0)
    {
      currentNodes.push_back(tokens[i]);
      break;
    }
    if (tokens[i].tokenType == TokenType::AS || tokens[i].tokenType == TokenType::THEN || tokens[i].tokenType == TokenType::REPEAT)
      ++depth;
    currentNodes.push_back(tokens[i]);
  }
  return currentNodes;
}

void AST::incrementToKeyword(int &i, const std::vector<Token> &tokens, std::vector<Token> &currentNodes, TokenType keyword)
{
  for (; i < tokens.size(); ++i)
  {
    currentNodes.push_back(tokens[i]);
    if (tokens[i].tokenType == keyword)
    {
      ++i;
      break;
    }
  }
}

variant<BinaryExpression, IntegerLiteral> AST::evaluateExpression(const vector<Token> &statement)
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

  return *binaryExpression;
}

shared_ptr<VariableStatement> AST::evaluateVariableStatement(const vector<Token> &statement)
{
  string identifier = statement[1].tokenString;

  vector<Token> expressionTokens;
  for (int i = 3; i < statement.size() - 1; ++i)
    expressionTokens.push_back(statement[i]);

  variant<BinaryExpression, IntegerLiteral> expression = evaluateExpression(expressionTokens);
  return make_shared<VariableStatement>(identifier, expression);
}

shared_ptr<FunctionStatement> AST::evaluateFunctionStatement(const vector<Token> &statement)
{
  string identifier = statement[1].tokenString;
  vector<string> parameters;

  // This is where the opening curly bracket is
  int startOfFunctionBody = 3;

  // The function has parameters
  if (statement[2].tokenType == TokenType::WITH)
  {
    // int i = 3;
    // for (; i < statement.size(); ++i)
    // {
    //   if (statement[i].tokenType == TokenType::COMMA)
    //     continue;
    //   if (statement[i].tokenType == TokenType::AS)
    //     break;
    //   parameters.push_back(statement[i].tokenString);
    // }
    // startOfFunctionBody = i + 1;
  }
  ++startOfFunctionBody;

  vector<Token> functionBodyTokens;

  extractBody(startOfFunctionBody, statement, functionBodyTokens);

  vector<shared_ptr<ASTNode>> functionBody = constructAST(functionBodyTokens).get()->nodes;
  return make_shared<FunctionStatement>(identifier, functionBody, parameters);
}

shared_ptr<IfStatement> AST::evaluateIfStatement(const vector<Token> &statement)
{
  vector<Token> expressionTokens;
  // We start at i = 1 since we want to ignore the if keyword, it's served it's purpose :)
  int i = 1;
  for (; statement[i].tokenType != TokenType::THEN; ++i)
    expressionTokens.push_back(statement[i]);

  variant<BinaryExpression, IntegerLiteral> evaluatedExpression = evaluateExpression(expressionTokens);
  vector<Token> ifStatementBodyTokens;

  extractBody(++i, statement, ifStatementBodyTokens);

  vector<shared_ptr<ASTNode>> ifStatementBody = constructAST(ifStatementBodyTokens).get()->nodes;
  return make_shared<IfStatement>(evaluatedExpression, ifStatementBody);
}

shared_ptr<Root> AST::constructAST(const vector<Token> &tokens)
{
  Root rootNode;

  vector<Token> currentNodes;
  for (int i = 0; i < tokens.size(); ++i)
  {
    currentNodes.push_back(tokens[i]);
    std::shared_ptr<ASTNode> newNode = nullptr;

    if (tokens[i].tokenType == TokenType::STOP)
    {
      newNode = evaluateVariableStatement(currentNodes);
    }
    else if (tokens[i].tokenType == TokenType::IF)
    {
      incrementToKeyword(++i, tokens, currentNodes, TokenType::THEN);
      extractBody(i, tokens, currentNodes);

      newNode = evaluateIfStatement(currentNodes);
    }
    else if (tokens[i].tokenType == TokenType::DEFINE)
    {
      incrementToKeyword(++i, tokens, currentNodes, TokenType::AS);
      extractBody(i, tokens, currentNodes);

      newNode = evaluateFunctionStatement(currentNodes);
    }

    if (newNode != nullptr)
    {
      rootNode.nodes.push_back(newNode);
      currentNodes.clear();
    }
  }

  return make_shared<Root>(rootNode);
}
