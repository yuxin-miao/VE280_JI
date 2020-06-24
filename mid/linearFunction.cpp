#include "linearFunction.h"

LinearFunction::LinearFunction(Vector a, Vector b):a1(a), a2(b) {
}

Vector LinearFunction::evaluate(Vector &v) {
   double x = a1.dot(v);
   double y = a2.dot(v);

   return Vector(x, y);
}

Vector LinearFunction::str() {
   return '(' + a1.str() + ", " + a2.str() + ")";
}
