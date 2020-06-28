#include "linearMap.h"
#ifndef positiveLinearMap_h
#define positiveLinearMap_h
// EFFECTS:
class PositiveLinearMap {

   LinearMap lm;

public:
   explicit PositiveLinearMap(Vector &a);

   double evaluate(Vector &v);
   std::string str();
};
#endif
