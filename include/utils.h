#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cctype>
#include <set>
#include <algorithm>
#include "token.h"

std::vector<std::string> splitString(std::string &input, std::set<std::string> &delimeters);
bool isInteger(std::string &input);
bool isDouble(std::string &input);
bool isOperator(TokenType tokenType);

#endif