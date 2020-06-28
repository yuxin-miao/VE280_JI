#include <string>
#include "vector.h"
#ifndef linearFunction_h
#define linearFunction_h
class LinearFunction {
    LinearFunction(Vector a, Vector b);

    Vector a1;
   Vector a2;

public:

   LinearFunction(Vector &x, Vector &y);

   Vector evaluate(Vector &v);
   Vector str();
};
#endif
