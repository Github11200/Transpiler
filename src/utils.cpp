#include "utils.h"

using namespace std;

vector<string> splitString(string &input, set<string> &delimiters)
{
  vector<string> strings;
  string currentString = "";

  for (char character : input)
  {
    if (iscntrl(static_cast<unsigned char>(character)))
      continue;
    if (delimiters.contains(currentString) || delimiters.contains(string(1, character)))
    {
      if (currentString != "" && currentString != " ")
        strings.push_back(currentString);
      if (delimiters.contains(string(1, character)))
      {
        strings.push_back(string(1, character));
        currentString = "";
      }
      else
        currentString = string(1, character);
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
      tokenType == TokenType::TIMES ||
      tokenType == TokenType::DIVIDE)
    return true;
  return false;
}

template <class T>
void printVector(const vector<T> &inputVector)
{
  for (auto element : inputVector)
    cout << element << endl;
}