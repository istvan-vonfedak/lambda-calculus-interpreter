#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <string>
#include "Lambda.hpp"

// this class holds a string variable
class Variable : public Lambda {
 public:
  std::string name;

  Variable()
  { this->name = ""; }

  Variable(std::string name)
  { this->name = name; }

  // used to determine which subclass the class is
  virtual bool isVar() { return true; }
  virtual bool isAbs() { return false; }
  virtual bool isApp() { return false; }
  // this function returns the variable name
  virtual std::string getName() { return name; }
  virtual Lambda * getVar() { return NULL; }
  virtual Lambda * getBody() { return NULL; }
  virtual Lambda * getFun() { return NULL; }
  virtual Lambda * getArg() { return NULL; }
};

#endif /* VARIABLE_HPP */
