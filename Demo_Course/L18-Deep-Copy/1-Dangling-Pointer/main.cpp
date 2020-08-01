#include <iostream>
#include "IntSet.h"

using namespace std;

void foo(IntSet x){
}

int main(){
    IntSet s;
    s.insert(5);
    s.print();

    foo(s);

//    {
//        IntSet x;
//        x = s; // x and s would have a pointer pointing to the same array
//                  when x is destroyed after this block, pointer in s becomes a dangling pointer
//    }
    s.print();

    return 0;
}
