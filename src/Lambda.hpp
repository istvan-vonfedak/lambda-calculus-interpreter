#ifndef LAMBDA_HPP
#define LAMBDA_HPP
#include <string>

// abstract class that is used as a base for
// building the lambda variable, abtract and application

class Lambda {
 public:
  // used to determine which subclass the class is
  virtual bool isVar() = 0;
  virtual bool isAbs() = 0;
  virtual bool isApp() = 0;

  // function used by Variable class
  virtual std::string getName() = 0;
  // functions used by Abstraction class
  virtual Lambda * getVar() = 0;
  virtual Lambda * getBody() = 0;
  // functions used by Application class
  virtual Lambda * getFun() = 0;
  virtual Lambda * getArg() = 0;
};

#endif /* LAMBDA_HPP */
