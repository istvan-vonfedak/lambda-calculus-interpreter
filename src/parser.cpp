#include "parser.hpp"

Lambda * parser(const std::vector<std::string> & tokens, int & i)
{ if(tokens.empty()) return NULL;
  if(tokens.size() <= i) return NULL;
  // create application
  if(tokens[i] == "(")
  { Application * result = new Application();
    i += 1;
    result->fun = parser(tokens, i);
    // i += 1;
    result->arg = parser(tokens, i);
    i += 1;
    return (Lambda *) result; }
  // create abstraction
  else if(tokens[i] == "#")
  { Abstraction * result = new Abstraction();
    i += 1;
    result->var = parser(tokens, i);
    if(tokens[i] != ".")
    { std::cout<<std::string(i,' ')<<"        ^ on this char\n";
      std::cout<<"Error in parser: Abstraction is not separated by period\n";
      exit(-1); }
    i += 1;
    result->body = parser(tokens, i);
    return (Lambda *) result; }
  else if(isVarChar(tokens[i][0]))
  { Variable * result = new Variable();
    result->name = tokens[i];
    i += 1;
    return (Lambda *) result; }
  // detect error for when app doesn't have two entries
  else if(tokens[i] == ")")
  { std::cout<<std::string(i,' ')<<"        ^ on this char\n";
    std::cout<<"Error in parser: Application doesn't contain two expressions\n";
    exit(-1); }
  else
  { std::cout<<std::string(i,' ')<<"        ^ on this char\n";
    std::cout<<"Error in parser: Unkown char = "<<tokens[i]<<std::endl;
    exit(-1); }}

Lambda * parser(std::vector<std::string> tokens)
{ int i = 0;
  return parser(tokens, i); }

void print(Lambda * ptr, const int & n)
{ if(ptr == NULL) return;
  // print space
  std::cout<<std::string(n,' ');
  // print rest
  if(ptr->isVar())
  { std::cout<<"Variable: "<<((Variable *) ptr)->name<<std::endl; }
  else if(ptr->isAbs())
  { std::cout<<"Abstraction:\n";
    Abstraction * temp = (Abstraction *) ptr;
    print(temp->var, n+1);
    std::cout<<std::string(n+1,' ')<<"body:\n";
    print(temp->body, n+2); }
  else
  { std::cout<<"Application:\n";
    Application * temp = (Application *) ptr;
    std::cout<<std::string(n+1,' ')<<"fun:\n";
    print(temp->fun, n+2);
    std::cout<<std::string(n+1,' ')<<"arg:\n";
    print(temp->arg, n+2); } }

void printSimple(Lambda * ptr)
{ if(ptr == NULL) return;

  // if var print var
  if(ptr->isVar())
  { std::cout<<((Variable *) ptr)->name; }

  // if abs pring abs
  else if(ptr->isAbs())
  { std::cout<<"#";
    Abstraction * abs = (Abstraction *) ptr;

    // print var
    printSimple(abs->var);
    std::cout<<".";

    // print body
    printSimple(abs->body); }

  // if app print app
  else if(ptr->isApp())
  { std::cout<<"(";
    Application * app = (Application *) ptr;

    // print fun
    printSimple(app->fun);
    std::cout<<" ";

    // print arg
    printSimple(app->arg);
    std::cout<<")"; }
  // if ptr type is unknown print error
  else
  { std::cout<<"Error in printSimple: ptr of unknown type\n";
    exit(-1); } }
