#include <iostream>
#include "anInt.h"
using namespace std;

void addOne(anInt i){
    // class objects are passed by value, not reference
    i.setValue(i.getValue() + 1);
}
void addOne_true(anInt *ip) {
    ip->setValue(ip->getValue() + 1);
}
int main(){
   anInt o; // declare objects of type anInt
   o.setValue(0);
   //cout << o.v << endl;  WRONG: because v is private, can't get directly

   addOne(o);
   cout << o.getValue() << endl;
   addOne_true(&o);
   cout << o.getValue() << endl;
}

