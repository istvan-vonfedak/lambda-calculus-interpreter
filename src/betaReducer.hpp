#ifndef BETAREDUCER_HPP
#define BETAREDUCER_HPP

#include "parser.hpp"

// deep copies a complex tree
Lambda * deepCopy(Lambda * ptr);

// beta reduction on variable
Lambda * betaReductionVar(Lambda * ptr, Lambda * var, Lambda * replacement);

// beta reduction on abstraction
Lambda * betaReductionAbs(Lambda * ptr, Lambda * var, Lambda * replacement);

// beta reduction on application
Lambda * betaReductionApp(Lambda * ptr, Lambda * var, Lambda * replacement);

// performs beta reduction on complex tree
Lambda * betaReduction(Lambda * ptr, Lambda * var, Lambda * replacement);


// perform recursive beta reductions until its fully reduced
Lambda * betaReducer(Lambda * ptr);

#endif /* BETAREDUCER_HPP */

