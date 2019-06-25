#include "lexicalAnalizer.hpp"

bool isVarChar(const char & c)
{ if(c >= 'a' && c <= 'z')
    return true;
  if(c >= 'A' && c <= 'Z')
    return true;
  if(c >= '0' && c <= '9')
    return true;
  if(c == '_')
    return true;
  return false; }

void testAppendingVar(bool & appendingVar, std::string & token, std::vector<std::string> & tokens)
{ if(appendingVar == true)
  { appendingVar = false;
    tokens.push_back(token);
    token.clear(); } }

void closeParensAssert(const std::vector<char> & parens, const int & spaces)
{ // test to see if parens is not empty
  if(parens.empty())
  { std::cout<<std::string(spaces,' ')<<"        ^ on this char\n";
    std::cout<<"Error missing open parenthesis\n";
    exit(-1); } }

void openParensAssert(const std::vector<char> & parens, const int & spaces)
{ // test to see if empty
  if(parens.empty() == false)
  { std::cout<<std::string(spaces,' ')<<"        ^ on this char\n";
    std::cout<<"Error missing close parenthesis\n";
    exit(-1); } }

void periodAssert(const std::vector<std::string> & tokens, const int & spaces)
{ const int size = tokens.size();
  if(isVarChar(tokens[size-1][0]) == false)
  { std::cout<<std::string(spaces,' ')<<"        ^ on this char\n";
    std::cout<<"Error token before period is not a variable\n";
    exit(-1); }
  if(tokens[size-2] != "#")
  { std::cout<<std::string(spaces,' ')<<"        ^ on this char\n";
    std::cout<<"Error second token before perion is not #\n";
    exit(-1); } }

void lexicalAnalizer(const std::string & str, std::vector<std::string> & tokens)
{ // token used to store temp vars
  std::string token;
  // keeps track of parenthesis
  std::vector<char> parens;
  bool appendingVar = false;
  for(int i = 0; i < str.length(); i++)
  { if(str[i] == ' ')
    {  testAppendingVar(appendingVar, token, tokens); }
    else if(str[i] == '#')
    { testAppendingVar(appendingVar, token, tokens);
      tokens.push_back("#"); }
    else if(str[i] == '(')
    { testAppendingVar(appendingVar, token, tokens);
      tokens.push_back("(");
      // push back a parenthesis to keep track of order
      parens.push_back('('); }
    else if(str[i] == ')')
    { testAppendingVar(appendingVar, token, tokens);
      tokens.push_back(")");
      // check to see if there are too many open parens
      closeParensAssert(parens, i);
      // pop back parenthesis to keep track of order
      parens.pop_back(); }
    else if(str[i] == '.')
    { testAppendingVar(appendingVar, token, tokens);
      periodAssert(tokens, i);
      tokens.push_back("."); }
    else if(isVarChar(str[i]))
    { if(appendingVar == false) appendingVar = true;
      token += str[i]; }
    else
    { std::cout<<std::string(i,' ')<<"        ^ invalid char\n";
      exit(-1); } }
  // check to see if there are too few close parens
  openParensAssert(parens, str.size());
  testAppendingVar(appendingVar, token, tokens); }

