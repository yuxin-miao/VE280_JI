#include "vector.h"
// EFFECTS:
class LinearFunction {
   Vector a1;
   Vector a2;

public:

   LinearFunction(Vector &x, Vector &y);

   Vector evaluate(Vector &v);
   std::string str();
};
