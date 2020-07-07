#include <iostream>
#include "IntSet.h"

using namespace std;
/**Deep copy**/
void foo(IntSet x){
    cout << "In function foo" << endl;
}

int main() {

    IntSet s(10);
    s.insert(5);

    foo(s); // the copy constructor is called
    s.query(5);
    cout << "s: ";
    s.print();

    {
        cout << "In the block: "<< endl;
        IntSet x;
        x = s;
        cout << "x: ";
        x.print();
    }

    s.query(5);
    s.print();

    return 0;
}
