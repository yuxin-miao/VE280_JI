#include <iostream>
#include "IntSet.h"

using namespace std;
/**shallow copy**/
void foo(IntSet x){
} // the local variable will be destroyed, the destructor of x is called

int main(){
    IntSet s;
    s.insert(5);
    s.print();

//    foo(s);
//    s.print(); //passed by value

    {
        IntSet x;
        x = s; // the array in s will be destroyed, when leaving the block
    }
    s.print();

    return 0;
}
