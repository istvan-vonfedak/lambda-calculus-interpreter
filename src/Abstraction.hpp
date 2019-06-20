#ifndef ABSTRACTION_HPP
#define ABSTRACTION_HPP
#include <string>
#include "Lambda.hpp"

// this class holds an abstraction
// == #Variable.#
// similar to a function
class Abstraction : public Lambda {
 public:
  Lambda * var;
  Lambda * body;

  Abstraction()
  { var = NULL;
    body = NULL; }

  virtual ~Abstraction()
  { delete var;
    delete body; }

  // used to determine which subclass the class is
  virtual bool isVar() { return false; }
  virtual bool isAbs() { return true; }
  virtual bool isApp() { return false; }

  virtual std::string getName() { return ""; }
  virtual Lambda * getVar() { return var; }
  virtual Lambda * getBody() { return body; }
  virtual Lambda * getFun() { return NULL; }
  virtual Lambda * getArg() { return NULL; }
};

#endif /* ABSTRACTION_HPP */
