#include "lexer.h"

using namespace std;

char Lexer::peekCharacter()
{
  if (index + 1 < sourceCode.size())
    return sourceCode[index + 1];
  throw "Index out of size";
}

char Lexer::consumeCharacter()
{
  char character = peekCharacter();
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

  operators.insert("=");
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

  this->sourceCode = sourceCode;
}

vector<Token> Lexer::getTokens()
{
  vector<Token> tokens;
  for (; index < sourceCode.size(); ++index)
  {
    if (sourceCode[index] == ' ')
      continue;
    string nextCharacter(1, peekCharacter());
    Token token(TokenType::IDENTIFIER, "");

    if (punctuator.contains(nextCharacter))
    {
      if (nextCharacter == ";")
      {
        token.tokenType = TokenType::SEMICOLON;
        token.tokenString = ";";
      }
      else if (nextCharacter == "{")
      {
        token.tokenType = TokenType::OPENING_CURLY_BRACKET;
        token.tokenString = "{";
      }
      else if (nextCharacter == "}")
      {
        token.tokenType = TokenType::CLOSING_CURLY_BRACKET;
        token.tokenString = "}";
      }
      else if (nextCharacter == "\"")
      {
        token.tokenType = TokenType::QUOTE;
        token.tokenString = "\"";
      }
      else if (nextCharacter == ",")
      {
        token.tokenType = TokenType::COMMA;
        token.tokenString = ",";
      }
      tokens.push_back(token);
      continue;
    }

    string nextWord = peekWord();
    
  }

  return tokens;
}