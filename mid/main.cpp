#include <iostream>

#include "vector.h"
#include "linearMap.h"
#include "positiveLinearMap.h"
#include "linearFunction.h"

using namespace std;

int main(){
      Vector v1(1, 1);
      Vector v2(2, 0);
      Vector v3(0.5, -4);
      Vector v4(3, 1);

      LinearFunction lf(v1, v2);
      LinearMap lm(v3);
      PositiveLinearMap plm(v4);

      cout << v1.toString() << endl;
      cout << v2.toString() << endl;
      cout << v3.toString() << endl;
      cout << v4.toString() << endl;

      cout << lf.str() << endl;
      cout << lm.str() << endl;
      cout << plm.str() << endl;

      cout << lf.evaluate(v3).toString() << endl;
      cout << lm.evaluate(v1) << endl;
      cout << plm.evaluate(v1) << endl;

      return 0;
}
