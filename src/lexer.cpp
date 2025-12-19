#include "lexer.h"

using namespace std;

Lexer::Lexer(string sourceCode)
{
  keywords.insert("let");
  keywords.insert("be");
  keywords.insert("pointer");
  keywords.insert("to");
  keywords.insert("stop");
  keywords.insert("define");
  keywords.insert("as");
  keywords.insert("end");
  keywords.insert("with");
  keywords.insert("if");
  keywords.insert("greater");
  keywords.insert("than");
  keywords.insert("then");
  keywords.insert("less");
  keywords.insert("or");
  keywords.insert("equal");
  keywords.insert("otherwise");
  keywords.insert("for");
  keywords.insert("repeat");

  set<string> delimeters = {" ", "stop", "then", "as", "end", "otherwise", "repeat"};
  this->splitSourceCode = splitString(sourceCode, delimeters);
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

    if (keywords.contains(currentToken))
    {
      if (currentToken == "let")
        token.tokenType = TokenType::LET;
      else if (currentToken == "be")
        token.tokenType = TokenType::BE;
      else if (currentToken == "pointer")
        token.tokenType = TokenType::POINTER;
      else if (currentToken == "to")
        token.tokenType = TokenType::TO;
      else if (currentToken == "stop")
        token.tokenType = TokenType::STOP;
      else if (currentToken == "define")
        token.tokenType = TokenType::DEFINE;
      else if (currentToken == "as")
        token.tokenType = TokenType::AS;
      else if (currentToken == "end")
        token.tokenType = TokenType::END;
      else if (currentToken == "if")
        token.tokenType = TokenType::IF;
      else if (currentToken == "greater")
        token.tokenType = TokenType::GREATER;
      else if (currentToken == "than")
        token.tokenType = TokenType::THAN;
      else if (currentToken == "then")
        token.tokenType = TokenType::THEN;
      else if (currentToken == "less")
        token.tokenType = TokenType::LESS;
      else if (currentToken == "or")
        token.tokenType = TokenType::OR;
      else if (currentToken == "or")
        token.tokenType = TokenType::OR;
      else if (currentToken == "equal")
        token.tokenType = TokenType::EQUAL;
      else if (currentToken == "otherwise")
        token.tokenType = TokenType::OTHERWISE;
      else if (currentToken == "for")
        token.tokenType = TokenType::FOR;
      else if (currentToken == "repeat")
        token.tokenType = TokenType::REPEAT;
    }

    if (token.tokenType != TokenType::IDENTIFIER)
    {
      token.tokenString = currentToken;
      tokens.push_back(token);
      continue;
    }

    if (isInteger(currentToken))
      token.tokenType = TokenType::INTEGER_LITERAL;
    else if (!keywords.contains(currentToken))
      token.tokenType = TokenType::IDENTIFIER;
    else
      throw "What are you doing.";

    token.tokenString = currentToken;
    tokens.push_back(token);
  }

  return tokens;
}
