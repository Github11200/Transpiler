#include "utils.h"

using namespace std;

vector<string> splitString(string &input, set<string> &delimeters)
{
  vector<string> strings;
  string currentString = "";

  for (char character : input)
  {
    if (delimeters.contains(string(1, character)))
    {
      strings.push_back(currentString);
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