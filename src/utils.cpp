#include "utils.h"

using namespace std;

vector<string> splitString(string &input, set<string> &delimiters)
{
  vector<string> strings;
  string currentString = "";

  for (char character : input)
  {
    if (delimiters.contains(string(1, character)))
    {
      if (currentString != "")
        strings.push_back(currentString);
      strings.push_back(string(1, character));
      currentString = "";
    }
    else
      currentString += character;
  }

  if (currentString != "")
    strings.push_back(currentString);
  return strings;
}

bool isInteger(std::string &input)
{
  return all_of(input.begin(), input.end(), ::isdigit);
}

bool isDouble(std::string &input)
{
  for (char c : input)
    if (!isdigit(c) && c != '.')
      return false;
  return true;
}

bool isOperator(TokenType tokenType)
{
  if (tokenType == TokenType::PLUS ||
      tokenType == TokenType::MINUS ||
      tokenType == TokenType::MULTIPLY ||
      tokenType == TokenType::DIVIDE)
    return true;
  return false;
}