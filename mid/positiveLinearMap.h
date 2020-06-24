#include "linearMap.h"
// EFFECTS:
class PositiveLinearMap {

   linearMap lm;

public:
   PositiveLinearMap(Vector &a);

   double evaluate(Vector &v);
   std::string str();
}
