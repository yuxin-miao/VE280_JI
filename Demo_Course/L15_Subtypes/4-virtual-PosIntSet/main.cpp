#include <iostream>
#include "IntSet.h"

using namespace std;

int main() {
    PosIntSet s;
    try {
        cout << "Insert -1 through s itself" << endl;
        s.insert(-1); // exception occur
        cout << "Insertion successful!" << endl;
    } catch (int i) {
        cout << "Exception thrown" << endl;
        cout << "Insertion failed!" << endl;
    }
    IntSet& r = s;
    //C++ allows a reference or pointer of a base type to refer to an object of a derived type.
    // not inverse s.t. PosIntSet &ws = r
    //While implicit downcasts are prohibited, we can do explicit downcasts with static_cast:
    PosIntSet &cs = static_cast<PosIntSet&>(r);
    try {
        cout << "Insert -2 through the reference to s" << endl;
        r.insert(-2); // exception, not successful anymore
        // because virtual -> virtual table -> choose PosIntSet::insert, not IntSet::insert
        cout << "Insertion successful!" << endl;
    } catch (int i) {
        cout << "Exception thrown" << endl;
        cout << "Insertion failed!" << endl;
    }
    IntSet* p = &s;
    try {
        cout << "Insert -3 through the pointer to s" << endl;
        p->insert(-3);
        cout << "Insertion successful!" << endl;
    } catch (int i) {
        cout << "Exception thrown" << endl;
        cout << "Insertion failed!" << endl;
    }

    s.print();
    return 0;
}
