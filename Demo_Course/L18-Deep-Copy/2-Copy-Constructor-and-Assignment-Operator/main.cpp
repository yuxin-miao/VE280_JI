#include <iostream>
#include "IntSet.h"

using namespace std;

void foo(IntSet x){
}

int main() {
    IntSet s(10);
    s.insert(5);
    s.print();

    foo(s); // copy constructor will copy s inside the function
    s.query(5);
    s.print();

    {
        IntSet x;
        x = s; // assignment operator, need the two objects both exist
        x.print();
    }

    s.query(5);
    s.print();

    return 0;
}
