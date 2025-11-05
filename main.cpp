#include <iostream>
#include "lexer.h"

using namespace std;

int main()
{
  Lexer lexer("define funcy as {}");
  vector<Token> tokens = lexer.getTokens();

  return 0;
}