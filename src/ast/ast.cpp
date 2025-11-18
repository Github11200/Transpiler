// #include "ast/ast.h"

// using namespace std;

// variant<unique_ptr<BinaryExpression>, unique_ptr<IntegerLiteral>> AST::evaluateExpression(vector<Token> &statement)
// {
//   // The statement is something like let x be 5;
//   if (statement.size() == 1)
//     return make_unique<IntegerLiteral>(IntegerLiteral(stoi(statement[0].tokenString)));

//   // We will assume it contains an operator otherwise
//   unique_ptr<BinaryExpression> binaryExpression = nullptr;
//   for (int i = 0; i < statement.size(); ++i)
//   {
//     if (!isOperator(statement[i].tokenType))
//       continue;

//     if (i + 1 == statement.size())
//       throw "An operand must be added after the operator.";

//     BinaryExpression newExpression(statement[i].tokenType, make_unique<IntegerLiteral>(stoi(statement[i - 1].tokenString)), make_unique<IntegerLiteral>(stoi(statement[i + 1].tokenString)));
//     if (binaryExpression != nullptr)
//       binaryExpression->right = make_unique<BinaryExpression>(newExpression);
//     else
//       binaryExpression = make_unique<BinaryExpression>(newExpression);
//   }
// }

// VariableStatement AST::evaluateVariableStatement(vector<Token> &statement)
// {
//   string identifier = statement[1].tokenString;

//   vector<Token> expressionTokens;
//   for (int i = 3; i < statement.size() - 1; ++i)
//     expressionTokens.push_back(statement[i]);

//   variant<unique_ptr<BinaryExpression>, unique_ptr<IntegerLiteral>> expression = evaluateExpression(expressionTokens);
//   return VariableStatement(identifier, make_unique<BinaryExpression>(expression));
// }

// unique_ptr<ASTNode> AST::evaluateStatement(vector<Token> &statement)
// {
//   /*
//   This is a variable statement: let x be 5;
//                                 ^^^   ^^
//                                 We're looking for these keywords
//   */
//   if (statement[0].tokenType == TokenType::LET && statement[2].tokenType == TokenType::BE)
//     return make_unique<VariableStatement>(evaluateVariableStatement(statement));
//   /*
//   This is a function statement: define x as {}
//                                 ^^^^^^   ^^
//                                 We're looking for these keywords
//   */
//   else if (statement[0].tokenType == TokenType::DEFINE && statement[2].tokenType == TokenType::AS)
//   {
//   }
// }

// Root AST::constructAST()
// {
//   Root rootNode;

//   vector<Token> currentStatement;
//   for (int i = 0; i < tokens.size(); ++i)
//   {

//     currentStatement.push_back(tokens[i]);
//   }

//   return rootNode;
// }