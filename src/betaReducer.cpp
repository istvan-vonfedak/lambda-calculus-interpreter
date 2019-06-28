#include "betaReducer.hpp"

// deep copies a complex tree
Lambda * deepCopy(Lambda * ptr)
{ // return NULL if ptr is NULL
  if(ptr == NULL) return NULL;
  // return copy of var if ptr is var
  else if(ptr->isVar())
  { Variable * result = new Variable();
    result->name = ((Variable *) ptr)->name;
    return result; }
  // return copy of abs if ptr is abs
  else if(ptr->isAbs())
  { Abstraction * result = new Abstraction();
    result->var = deepCopy(((Abstraction *) ptr)->var);
    result->body = deepCopy(((Abstraction *) ptr)->body);
    return result; }
  // return copy of app if ptr is app
  else
  { Application * result = new Application();
    result->fun = deepCopy(((Application *) ptr)->fun);
    result->arg = deepCopy(((Application *) ptr)->arg);
    return result; } }

// beta reduction on variable
Lambda * betaReductionVar(Lambda * ptr, Lambda * var, Lambda * replacement)
{ if(ptr == NULL) return NULL;

  // if not a variable throw error
  else if(ptr->isVar() == false)
  { std::cout<<"Error in betaReductionVar(...): ptr->isVar() == false\n";
    exit(-1); }

  else if(var == NULL && replacement != NULL)
  { std::cout<<"Error in betaRaductionVar(...): var == NULL && replacement != NULL\n";
    exit(-1); }

  else if(var != NULL && replacement == NULL)
  { std::cout<<"Error in betaRaductionVar(...): var != NULL && replacement == NULL\n";
    exit(-1); }

  // if no beta reduction was done then return NULL
  // to symbolize that there was no replacement
  else if(var == NULL)
    return NULL;

  // if replacement == NULL throw error
  else if(replacement == NULL)
  { std::cout<<"Error in betaReductionVar(...): var != NULL and replacement == NULL\n";
    exit(-1); }

  // if the variable is the same as the replacement variable
  // return a deep copy of the replacement
  else if(((Variable *) ptr)->name == ((Variable *) var)->name)
    // copy and return the replacement
    return deepCopy(replacement);

  // else return NULL to symbolize that there was no replacement
  else
    return NULL; }

// beta reduction on abstraction
Lambda * betaReductionAbs(Lambda * ptr, Lambda * var, Lambda * replacement)
{ if(ptr == NULL) return NULL;

  else if(var != NULL && replacement == NULL)
  { std::cout<<"Error in betaRaductionAbs(...): var != NULL && replacement == NULL\n";
    exit(-1); }

  // if ptr is not an abstraction throw error
  else if(ptr->isAbs() == false)
  { std::cout<<"Error in betaReductionAbs(...): ptr->isAbs() == false\n";
    exit(-1); }

  Abstraction * abs = (Abstraction *) ptr;

  // make sure ptr is complete
  if(abs->var == NULL || abs->body == NULL)
  { std::cout<<"Error in betaReductionABs(...): (ptr->var == NULL || ptr->body == NULL\n";
    exit(-1); }

  // do beta reduction on the body of the abstraction
  Lambda * body = betaReduction(abs->body, NULL, NULL);

  // if replacement is not NULL use the variable in the abstraction for beta reduction
  // case where the var of the abs is used in beta reduction
  if(var == NULL && replacement != NULL)
  { // this will be used to represent the outcome of the beta reduction
    Lambda * outcome = NULL;
    // if body can't be reduced, reduce it with the original body
    if(body == NULL)
      outcome = betaReduction(abs->body, abs->var, replacement);
    // else reduce with the reduced body
    else
      outcome = betaReduction(body, abs->var, replacement);

    // if the body of the abs was reduced then return the outcome
    if(outcome != NULL)
    { // make sure to delete the body
      if(body != NULL) delete body;
      return outcome; }
    // if it wasn't reduced check if body was reduced
    else
    { // if body was reduced then return a new abs with the new body
      if(body != NULL)
      { Abstraction * result = new Abstraction();
        // copy var
        result->var = deepCopy(abs->var);
        result->body = body;
        return result; }
      // else return NULL to state that nothing was reduced
      else
        return NULL; } }

  // else just continue doing beta reductions
  // need to check if var and body can be beta reduced
  else
  { // variables used for return
    // try to reduce the var in the abs
    Lambda * newVar = betaReductionVar(abs->var, var, replacement);
    Lambda * newBody;

    // if body can't be reduced, reduce it with the original body
    if(body == NULL)
      newBody = betaReduction(abs->body, var, replacement);

    // else used the reduced body for the reduction
    else
    { newBody = betaReduction(body, var, replacement); }

    // if both of them can't be reduced, return NULL if body wasn't able to be reduced
    if(newVar == NULL && newBody == NULL && body == NULL)
    { return NULL; }

    // create result
    Abstraction * result = new Abstraction();
    // copy var depending on wether it was able to be reduced
    result->var = (newVar == NULL)? deepCopy(abs->var) : newVar;

    // if you could only reduce the body return a new abs with the reduced body
    if(newBody == NULL && body != NULL)
    { // set the reduced body as the new body
      result->body = body;
      return result; }

    // after this point we don't need body becasue its infor is reflected on the
    // result of the new body
    if(body != NULL) delete body;

    result->body = (newBody == NULL)? deepCopy(abs->body) : newBody;
    return (Lambda *) result; } }

// beta reduction on application
Lambda * betaReductionApp(Lambda * ptr, Lambda * var, Lambda * replacement)
{ if(ptr == NULL) return NULL;

  else if(var == NULL && replacement != NULL)
  { std::cout<<"Error in betaRaductionApp(...): var == NULL && replacement != NULL\n";
    exit(-1); }

  else if(var != NULL && replacement == NULL)
  { std::cout<<"Error in betaRaductionApp(...): var != NULL && replacement == NULL\n";
    exit(-1); }

  // if ptr is not an application throw error
  else if(ptr->isApp() == false)
  { std::cout<<"Error in betaReductionApp(...): ptr->isApp() == false\n";
    exit(-1); }

  Application * app = (Application *) ptr;

  // make sure ptr is complete
  if(app->fun == NULL || app->arg == NULL)
  { std::cout<<"Error in betaReductionApp(..): ptr->fun == NULL || ptr->arg == NULL)\n";
    exit(-1); }

  // if there is no var to be substituted and fun is an abstraction perform beta reduction using
  // the argument and the abstraction
  if(var == NULL && app->fun->isAbs())
  { // perform beta reduction on the arg of the app
    Lambda * arg = betaReduction(app->arg, NULL, NULL);

    // if you couldn't reduce the arg deep copy the original arg
    if(arg == NULL) arg = deepCopy(app->arg);

    // do beta reduction on the abstraction
    Lambda * outcome = betaReduction(app->fun, NULL, arg);

    // make sure you delete arg after using it
    if(arg != NULL) delete arg;

    // if you couldn't reduce the abstraction return NULL
    if(outcome == NULL)
      return NULL;

    // if beta reduction was sucessful with the application return the outcome
    else
      return outcome; }

  // if var is not NULL do beta reduction on both the fun and the arg
  else
  { // try to perform beta reduction on both the fun and arg
    Lambda * newFun = betaReduction(app->fun, var, replacement);
    Lambda * newArg = betaReduction(app->arg, var, replacement);
    // if both of them are NULL return NULL
    if(newFun == NULL && newArg == NULL)
      return NULL;
    // else create a new application to be returned
    Application * result = new Application();
    result->fun = (newFun == NULL)? deepCopy(app->fun) : newFun;
    result->arg = (newArg == NULL)? deepCopy(app->arg) : newArg;
    return result; } }

// performs beta reduction on complex tree
Lambda * betaReduction(Lambda * ptr, Lambda * var, Lambda * replacement)
{ if(ptr == NULL) return NULL;

  // check to see if its an variable
  else if(ptr->isVar())
    return betaReductionVar(ptr, var, replacement);

  // check to see its an abstraction
  else if(ptr->isAbs())
    return betaReductionAbs(ptr, var, replacement);

  // do beta reduction on application
  else if(ptr->isApp())
    return betaReductionApp(ptr, var, replacement);
  else
  { std::cout<<"Error in betaReduction(...) Lambda * ptr is of unknown type\n";
    exit(-1); } }


// perform recursive beta reductions until its fully reduced
Lambda * betaReducer(Lambda * ptr)
{ if(ptr == NULL) return NULL;

  // set the prev result as NULL
  Lambda * prevResult = NULL;

  // obtain the beta reduction of the ptr
  Lambda * result = betaReduction(ptr, NULL, NULL);

  // if the result is NULL return copy of the ptr
  if(result == NULL) return deepCopy(ptr);

  // while you can still do beta reductions on the result
  while(result != NULL)
  { // delete previous result if its not NULL
    if(prevResult != NULL) delete prevResult;
    // set the result as the new previous result
    prevResult = result;
    // get the new beta reduction on the result
    result = betaReduction(result, NULL, NULL); }

  // once this loop finished prevResult will have the full beta reduction
  return prevResult; }

