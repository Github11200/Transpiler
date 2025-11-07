#include "ast/ast.h"

using namespace std;

Expression AST::evaluateExpression(vector<Token> &statement)
{
}

VariableStatement AST::evaluateVariableStatement(vector<Token> &statement)
{
  string identifier = statement[1].tokenString;

  vector<Token> expressionTokens;
  for (int i = 3; i < statement.size() - 1; ++i)
    expressionTokens.push_back(statement[i]);

  Expression expression = evaluateExpression(expressionTokens);
  return VariableStatement(identifier, expression);
}

unique_ptr<ASTNode> AST::evaluateStatement(vector<Token> &statement)
{
  /*
  This is a variable statement: let x be 5;
                                ^^^   ^^
                                We're looking for these keywords
  */
  if (statement[0].tokenType == TokenType::LET && statement[2].tokenType == TokenType::BE)
    return make_unique<VariableStatement>(evaluateVariableStatement(statement));
  /*
  This is a variable statement: define x as {}
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

  return rootNode;
}