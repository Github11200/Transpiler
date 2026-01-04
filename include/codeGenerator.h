#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "ast/node.h"
#include <iostream>
#include <memory>
#include <fstream>

class CodeGenerator
{
private:
  std::shared_ptr<Root> rootNode;

public:
  CodeGenerator(std::shared_ptr<Root> rootNode);
  void generate(std::string fileName);
};

#endif