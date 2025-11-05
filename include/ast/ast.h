#ifndef AST_H
#define AST_H

#include <concepts>
#include "ast/node.h"

class AST
{
public:
  AST();

  template <std::derived_from<ASTNode> Node>
  Node constructAST();
};

#endif