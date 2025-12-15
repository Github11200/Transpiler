#include "lexer.h"

using namespace std;

optional<char> Lexer::peekCharacter()
{
  if (index + 1 < sourceCode.size())
    return sourceCode[index + 1];
  return nullopt;
}

optional<char> Lexer::consumeCharacter()
{
  optional<char> character = peekCharacter();
  if (!character.has_value())
    return nullopt;
  ++index;
  return character;
}

string Lexer::peekWord()
{
  string word = "";
  for (int i = index; sourceCode[i] != ' ' && i < sourceCode.size(); ++i)
    word.push_back(sourceCode[i]);
  return sourceCode;
}

string Lexer::consumeWord()
{
  string word = peekWord();
  index += word.size();
  return word;
}

Lexer::Lexer(string sourceCode)
{
  keywords.insert("let");
  keywords.insert("if");
  keywords.insert("be");
  keywords.insert("point");
  keywords.insert("to");
  keywords.insert("define");
  keywords.insert("as");
  keywords.insert("repeat");
  keywords.insert("true");
  keywords.insert("false");
  keywords.insert("with");

  operators.insert("+");
  operators.insert("-");
  operators.insert("*");
  operators.insert("/");

  punctuator.insert(";");
  punctuator.insert("}");
  punctuator.insert("{");
  punctuator.insert("\"");
  punctuator.insert(",");
  punctuator.insert(" ");

  this->sourceCode = sourceCode;
  this->splitSourceCode = splitString(sourceCode, punctuator);
  this->index = 0;
}

vector<Token> Lexer::getTokens()
{
  vector<Token> tokens;
  for (; index < splitSourceCode.size(); ++index)
  {
    string currentToken = splitSourceCode[index];
    if (currentToken == " ")
      continue;

    Token token(TokenType::IDENTIFIER, " ");

    if (operators.contains(currentToken))
    {
      if (currentToken == "+")
        token.tokenType = TokenType::PLUS;
      else if (currentToken == "-")
        token.tokenType = TokenType::MINUS;
      else if (currentToken == "*")
        token.tokenType = TokenType::MULTIPLY;
      else if (currentToken == "/")
        token.tokenType = TokenType::DIVIDE;
    }

    if (keywords.contains(currentToken))
    {
      if (currentToken == "let")
        token.tokenType = TokenType::LET;
      else if (currentToken == "if")
        token.tokenType = TokenType::IF;
      else if (currentToken == "be")
        token.tokenType = TokenType::BE;
      else if (currentToken == "as")
        token.tokenType = TokenType::AS;
      else if (currentToken == "point")
        token.tokenType = TokenType::POINT;
      else if (currentToken == "define")
        token.tokenType = TokenType::DEFINE;
      else if (currentToken == "repeat")
        token.tokenType = TokenType::REPEAT;
      else if (currentToken == "true")
        token.tokenType = TokenType::TRUE;
      else if (currentToken == "false")
        token.tokenType = TokenType::FALSE;
      else if (currentToken == "with")
        token.tokenType = TokenType::WITH;
    }

    if (punctuator.contains(currentToken))
    {
      if (currentToken == ";")
        token.tokenType = TokenType::SEMICOLON;
      else if (currentToken == "{")
        token.tokenType = TokenType::OPENING_CURLY_BRACKET;
      else if (currentToken == "}")
        token.tokenType = TokenType::CLOSING_CURLY_BRACKET;
      else if (currentToken == "\"")
        token.tokenType = TokenType::QUOTE;
      else if (currentToken == ",")
        token.tokenType = TokenType::COMMA;
    }

    if (token.tokenType != TokenType::IDENTIFIER)
    {
      token.tokenString = currentToken;
      tokens.push_back(token);
      continue;
    }

    if (isInteger(currentToken))
      token.tokenType = TokenType::INTEGER_LITERAL;
    else if (isDouble(currentToken))
      token.tokenType = TokenType::FLOAT;
    else if (!punctuator.contains(currentToken))
      token.tokenType = TokenType::IDENTIFIER;
    else
      throw "What are you doing.";

    token.tokenString = currentToken;
    tokens.push_back(token);
  }

  return tokens;
}
