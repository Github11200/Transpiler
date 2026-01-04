#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cctype>
#include <set>
#include <algorithm>
#include <iostream>
#include "token.h"

std::vector<std::string> splitString(std::string &input, std::set<std::string> &delimiters);
bool isInteger(std::string &input);
bool isDouble(std::string &input);
bool isOperator(TokenType tokenType);

template <class T>
void printVector(const std::vector<T> &inputVector);

#endif