#include "ast/node.h"

using namespace std;

void Root::readValue()
{
  cout << "hi" << endl;
}

void IntegerLiteral::readValue()
{
  cout << value;
}

BinaryExpression::BinaryExpression(const TokenType operatorType, variant<BinaryExpression, IntegerLiteral> left,
                                   variant<BinaryExpression,
                                           IntegerLiteral>
                                       right)
{
  this->operatorType = operatorType;
  visit([&]<typename T>(const T &var)
        {
        if constexpr (is_same_v<decay_t<T>, BinaryExpression>)
            this->left = make_shared<BinaryExpression>(var);
        if constexpr (is_same_v<decay_t<T>, IntegerLiteral>)
            this->left = make_shared<IntegerLiteral>(var); }, left);

  visit([&]<typename T>(const T &var)
        {
        if constexpr (is_same_v<decay_t<T>, BinaryExpression>)
            this->right = make_shared<BinaryExpression>(var);
        if constexpr (is_same_v<decay_t<T>, IntegerLiteral>)
            this->right = make_shared<IntegerLiteral>(var); }, right);
}

void BinaryExpression::readValue()
{
  if (holds_alternative<shared_ptr<IntegerLiteral>>(left))
    get<shared_ptr<IntegerLiteral>>(left)->readValue();
  else if (holds_alternative<shared_ptr<BinaryExpression>>(left))
    get<shared_ptr<BinaryExpression>>(left)->readValue();

  switch (operatorType)
  {
  case TokenType::PLUS:
    cout << " + ";
    break;
  case TokenType::MINUS:
    cout << " - ";
    break;
  case TokenType::TIMES:
    cout << " * ";
    break;
  case TokenType::DIVIDE:
    cout << " / ";
    break;

  default:
    break;
  }

  if (holds_alternative<shared_ptr<IntegerLiteral>>(right))
    get<shared_ptr<IntegerLiteral>>(right)
        ->readValue();
  else if (holds_alternative<shared_ptr<BinaryExpression>>(right))
    get<shared_ptr<BinaryExpression>>(right)
        ->readValue();
}

VariableStatement::VariableStatement(const string &identifier,
                                     variant<BinaryExpression, IntegerLiteral> value)
{
  this->identifier = identifier;
  visit([&]<typename T>(const T &var)
        {
        if constexpr (is_same_v<decay_t<T>, BinaryExpression>)
            this->value = make_shared<BinaryExpression>(var);
        if constexpr (is_same_v<decay_t<T>, IntegerLiteral>)
            this->value = make_shared<IntegerLiteral>(var); }, value);
}

void VariableStatement::readValue()
{
  cout << this->identifier << ": ";
  if (holds_alternative<shared_ptr<IntegerLiteral>>(value))
    get<shared_ptr<IntegerLiteral>>(value)->readValue();
  else if (holds_alternative<shared_ptr<BinaryExpression>>(value))
    get<shared_ptr<BinaryExpression>>(value)->readValue();
  cout << endl;
}

FunctionStatement::FunctionStatement(const string &identifier, const vector<shared_ptr<ASTNode>> &body,
                                     const vector<string> &parameters)
{
  this->identifier = identifier;
  if (!parameters.empty())
    this->parameters = parameters;
  this->body = body;
}

void FunctionStatement::readValue()
{
  for (const auto &node : body)
    node.get()->readValue();
}

IfStatement::IfStatement(const variant<BinaryExpression, IntegerLiteral> condition, const vector<std::shared_ptr<ASTNode>> &body)
{
  visit([&]<typename T>(const T &var)
        {
        if constexpr (is_same_v<decay_t<T>, BinaryExpression>)
            this->condition = make_shared<BinaryExpression>(var);
        if constexpr (is_same_v<decay_t<T>, IntegerLiteral>)
            this->condition = make_shared<IntegerLiteral>(var); }, condition);
  this->body = body;
}

void IfStatement::readValue()
{
  if (holds_alternative<shared_ptr<BinaryExpression>>(condition))
    get<shared_ptr<BinaryExpression>>(condition)->readValue();
  cout << endl;
  for (const auto &bodyStatement : body)
    bodyStatement->readValue();
}