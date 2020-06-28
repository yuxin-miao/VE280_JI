#include "vector.h"
#ifndef linearMap_h
#define linearMap_h
class LinearMap {
   Vector a;

public:
   explicit LinearMap(Vector &a);

   double evaluate(Vector &v);
   std::string str();
};
#endif