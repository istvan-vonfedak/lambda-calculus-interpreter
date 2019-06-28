#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "lexicalAnalizer.hpp"
#include "Lambda.hpp"
#include "Variable.hpp"
#include "Abstraction.hpp"
#include "Application.hpp"


Lambda * parser(const std::vector<std::string> & tokens, int & i);

Lambda * parser(std::vector<std::string> tokens);

void print(Lambda * ptr, const int & n);

void printSimple(Lambda * ptr);

#endif /* PARSER_HPP */
