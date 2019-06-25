#ifndef LEXICALANALIZER_HPP
#define LEXIVALANALIZER_HPP

#include <iostream>
#include <string>
#include <vector>

bool isVarChar(const char & c);

void testAppendingVar(bool & appendingVar, std::string & token, std::vector<std:                                                                                             :string> & tokens);

void closeParensAssert(const std::vector<char> & parens, const int & spaces);

void openParensAssert(const std::vector<char> & parens, const int & spaces);

void periodAssert(const std::vector<std::string> & tokens, const int & spaces);

void lexicalAnalizer(const std::string & str, std::vector<std::string> & tokens)                                                                                             ;

#endif /* LEXICALANALIZER_HPP */

