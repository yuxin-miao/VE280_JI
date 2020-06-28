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
    IntSet& r = s; // because PosIntSet is a subclass of IntSet,
    // r could be the reference of PosIntSet s
    // r is declared as the reference to an IntSet (Apparent type), but actually refers to PosIntSet (Actual Type)
    // choose the method to run based on the apparent type
    try {
        cout << "Insert -2 through the reference to s" << endl;
        r.insert(-2); // so successful
        cout << "Insertion successful!" << endl;
    } catch (int i) {
        cout << "Exception thrown" << endl;
        cout << "Insertion failed!" << endl;
    }
    IntSet* p = &s; // p could be the pointer of PosIntSet s
    try {
        cout << "Insert -3 through the pointer to s" << endl;
        p->insert(-3); // successful
        cout << "Insertion successful!" << endl;
    } catch (int i) {
        cout << "Exception thrown" << endl;
        cout << "Insertion failed!" << endl;
    }

    // to avoid choosing the method of apparent type, add the keyword virtual
    // virtual: it might be override, check which version to call
    s.print();
    // For quiz, try the not virtual function - then virtual in subclass then subclass of subclass
    ZeroIntSet z;
    PosIntSet *p_to_z = &z;
    try {
        cout << "insert 4 through the pointer to ZeroIntSet z" << endl;
        p_to_z->insert(4);
        cout << "Insertion Successful" << endl;
    } catch (int i) {
        cout << "Exception thrown" << endl;
        cout << "Insertion failed!" << endl;
    }
    return 0;
}
