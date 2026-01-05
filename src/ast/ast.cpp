#include "ast/ast.h"

using namespace std;

bool AST::keywordIsStartOfNewCodeBlock(TokenType keyword)
{
  if (keyword == TokenType::AS || keyword == TokenType::THEN || keyword == TokenType::REPEAT)
    return true;
  return false;
}

vector<Token> AST::extractBody(int &i, const vector<Token> &tokens, TokenType keyword)
{
  int depth = 0;
  vector<Token> currentNodes;
  for (; i < tokens.size(); ++i)
  {
    if (tokens[i].tokenType == keyword && depth == 0)
      break;
    if (keywordIsStartOfNewCodeBlock(tokens[i].tokenType))
      ++depth;
    if (tokens[i].tokenType == TokenType::END)
      --depth;
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

  if (statement[3].tokenType == TokenType::POINTER)
    return make_shared<VariableStatement>(statement[5].tokenString);

  vector<Token> expressionTokens;
  for (int i = 3; i < statement.size() - 1; ++i)
    expressionTokens.push_back(statement[i]);

  variant<BinaryExpression, IntegerLiteral> expression = evaluateExpression(expressionTokens);
  return make_shared<VariableStatement>(identifier, expression);
}

shared_ptr<FunctionStatement> AST::evaluateFunctionStatement(const CodeBlock &functionBlock)
{
  string identifier = functionBlock.statement[1].tokenString;
  vector<string> parameters;

  // The function has parameters
  if (functionBlock.statement[2].tokenType == TokenType::WITH)
    for (int i = 3; functionBlock.statement[i].tokenType != TokenType::AS; ++i)
      parameters.push_back(functionBlock.statement[i].tokenString);

  vector<shared_ptr<ASTNode>> functionBody = constructAST(functionBlock.bodyTokens).get()->nodes;
  return make_shared<FunctionStatement>(identifier, functionBody, parameters);
}

shared_ptr<IfStatement> AST::evaluateIfStatement(const CodeBlock &ifBlock)
{
  vector<Token> expressionTokens;
  // We start at i = 1 since we want to ignore the if keyword, it's served it's purpose :)
  int i = 1;
  for (; ifBlock.statement[i].tokenType != TokenType::THEN; ++i)
    expressionTokens.push_back(ifBlock.statement[i]);

  int numberOfOtherwiseKeywords = 0;
  int depth = 0;
  int i = 0;
  vector<Token> blockBodyTokens;
  for (; i < ifBlock.bodyTokens.size(); ++i)
  {
    if (ifBlock.bodyTokens[i].tokenType == TokenType::OTHERWISE && depth == 0)
      ++numberOfOtherwiseKeywords;
    else if (keywordIsStartOfNewCodeBlock(ifBlock.bodyTokens[i].tokenType))
      ++depth;
    else if (ifBlock.bodyTokens[i].tokenType == TokenType::END)
      --depth;
  }

  vector<IfStatementBlock> ifStatementBlocks;

  for (int j = 0; j < numberOfOtherwiseKeywords; ++j)
  {
    vector<Token> currentBlockTokens;
    vector<Token> currentBlockStatement;
    int k = 0;

    // Check to make sure this isn't the last otherwise statement
    if (j + 1 < numberOfOtherwiseKeywords)
    {
    }

    extractBody(k, currentBlockTokens, TokenType::OTHERWISE);
    variant<BinaryExpression, IntegerLiteral> evaluatedExpression = evaluateExpression(ifBlock.statement);
  }

  return make_shared<IfStatement>(ifStatementBlocks);
}

shared_ptr<LoopStatement> AST::evaluateLoopStatement(const CodeBlock &loopBlock)
{
  // Loop from after the for keyword to before the repeat keyword
  vector<Token> expressionTokens;
  for (int i = 1; i < loopBlock.statement.size() - 1; ++i)
    expressionTokens.push_back(loopBlock.statement[i]);

  BinaryExpression evaluatedExpression = get<BinaryExpression>(evaluateExpression(expressionTokens));
  vector<shared_ptr<ASTNode>> loopStatementBody = constructAST(loopBlock.bodyTokens).get()->nodes;

  return make_shared<LoopStatement>(evaluatedExpression, loopStatementBody);
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
      newNode = evaluateIfStatement({.statement = currentNodes, .bodyTokens = extractBody(i, tokens)});
    }
    else if (tokens[i].tokenType == TokenType::DEFINE)
    {
      incrementToKeyword(++i, tokens, currentNodes, TokenType::AS);
      newNode = evaluateFunctionStatement({.statement = currentNodes, .bodyTokens = extractBody(i, tokens)});
    }
    else if (tokens[i].tokenType == TokenType::FOR)
    {
      incrementToKeyword(++i, tokens, currentNodes, TokenType::REPEAT);
      newNode = evaluateLoopStatement({.statement = currentNodes, .bodyTokens = extractBody(i, tokens)});
    }

    if (newNode != nullptr)
    {
      rootNode.nodes.push_back(newNode);
      currentNodes.clear();
    }
  }

  return make_shared<Root>(rootNode);
}
