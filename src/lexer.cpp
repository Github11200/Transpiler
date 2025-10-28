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
  keywords.insert("if");
  keywords.insert("be");
  keywords.insert("point");
  keywords.insert("to");
  keywords.insert("let");
  keywords.insert("define");
  keywords.insert("as");
  keywords.insert("repeat");

  operators.insert("<=");
  operators.insert(">=");
  operators.insert("==");
  operators.insert("++");
  operators.insert("--");

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
    Token token(TokenType::IDENTIFIER, "");

    if (punctuator.contains(currentToken))
    {
      if (currentToken == ";")
      {
        token.tokenType = TokenType::SEMICOLON;
        token.tokenString = ";";
      }
      else if (currentToken == "{")
      {
        token.tokenType = TokenType::OPENING_CURLY_BRACKET;
        token.tokenString = "{";
      }
      else if (currentToken == "}")
      {
        token.tokenType = TokenType::CLOSING_CURLY_BRACKET;
        token.tokenString = "}";
      }
      else if (currentToken == "\"")
      {
        token.tokenType = TokenType::QUOTE;
        token.tokenString = "\"";
      }
      else if (currentToken == ",")
      {
        token.tokenType = TokenType::COMMA;
        token.tokenString = ",";
      }
    }

    if (operators.contains(currentToken))
      token.tokenType = TokenType::OPERATOR;
    else if (keywords.contains(currentToken))
      token.tokenType = TokenType::KEYWORD;
    else if (isInteger(currentToken))
      token.tokenType = TokenType::INTEGER_LITERAL;
    else
      token.tokenType = TokenType::IDENTIFIER;

    token.tokenString = currentToken;
    tokens.push_back(token);
  }

  return tokens;
}
