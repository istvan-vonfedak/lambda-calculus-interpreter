#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <string>
#include "Lambda.hpp"

class Application : public Lambda {
 public:
  Lambda * fun;
  Lambda * arg;

  Application()
  { fun = NULL;
    arg = NULL; }

  virtual ~Application()
  { delete fun;
    delete arg; }

  // used to determine which subclass the class is
  virtual bool isVar() { return false; }
  virtual bool isAbs() { return false; }
  virtual bool isApp() { return true; }
  // functions needed for subclasses
  virtual std::string getName() { return ""; }
  virtual Lambda * getVar() { return NULL; }
  virtual Lambda * getBody() { return NULL; }
  virtual Lambda * getFun() { return fun; }
  virtual Lambda * getArg() { return arg; }
};

#endif /* APPLICATION_HPP */
