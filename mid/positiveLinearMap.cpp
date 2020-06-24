#include <iostream>
#include <sstream>
#include "positiveLinearMap.h"

PositiveLinearMap::PositiveLinearMap(Vector &a):lm(LinearMap(a)) {
   if (a.getX() <= 0 || a.getY() <= 0) throw a;
}

double PositiveLinearMap::evaluate(Vector &v) {
   return lm.dot(v);
}

std::string PositiveLinearMap::str() {
   return lm.str();
}
