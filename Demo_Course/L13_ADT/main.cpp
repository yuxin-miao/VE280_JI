#include <iostream>
#include "IntSet.h"

using namespace std;
// ADT : Abstract data type do not know the details of how the struct operates
// but focus on what the struct could do
int main(){
    IntSet foo;
    cout << "insert 7" << endl;
    foo.insert(7);
    foo.print();

    cout << "insert 3" << endl;
    foo.insert(3);
    foo.print();

    cout << "insert 4" << endl;
    foo.insert(4);
    foo.print();

    cout << "insert 5" << endl;
    foo.insert(5);
    foo.print();

    cout << "insert 7" << endl;
    foo.insert(7);
    foo.print();

    cout << "insert 8" << endl;
    foo.insert(8);
    foo.print();

    cout << "remove 5" << endl;
    foo.remove(5);
    foo.print();

    cout << "remove 8" << endl;
    foo.remove(8);
    foo.print();

    cout << "remove 6" << endl;
    foo.remove(6);
    foo.print();

    const IntSet con_ex;
    cout << con_ex.size(); //ok
    //con_ex.insert(2); WRONG, const object can only call const member functions

    return 0;
}
