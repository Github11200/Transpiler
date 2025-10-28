#include <iostream>
#include "lexer.h"

using namespace std;

int main()
{
  Lexer lexer("define x as 5;");
  vector<Token> tokens = lexer.getTokens();

  return 0;
}