#include <iostream>
using namespace std;

class Object { // a dummy class
public:
    virtual Object* clone() = 0; // for the copyList to do the deep copy
    virtual ~Object();
};


class BigThing : public Object{
public:
    Object* clone() override ;
    BigThing(const BigThing &b);

};

Object* BigThing::clone() {
    BigThing* bp = new BigThing(*this);
    return bp;
}
struct nodeP {
    nodeP* next;
    Object *value;
};
class ListP {

    nodeP *first;
    void removeAll();
    void copyList(nodeP *node);

public:
    bool isEmpty();
    // EFFECTS: returns true if list is empty, false otherwise
    void insert(Object* o);
    // MODIFIES: this
    // EFFECTS: inserts v into the front of the list
    Object* remove();
    // MODIFIES: this
    // EFFECTS: if list is empty, throw listIsEmpty.
    //          Otherwise, remove and return the first
    //          element of the list
    void print();
    // MODIFIES: cout
    // EFFECTS: print the int list

    ListP();
    // default constructor
    ListP(const ListP& l);
    // copy constructor
    ~ListP();
    // destructor
    ListP &operator=(const LisP &l);
    // assignment operator
};



int main() {
    BigThing *bp = new BigThing;
    ListP l;
    l.insert(bp); // legal by substitution rule

    Object* op;
    op = l.remove();
    bp = dynamic_cast<BigThing*>(op); // only works for classed which have one or more virtual methods
    // EFFECTS: if op's actual type is a pointer to BigThing or some pointer to derived class of BigThing
    // returns a pointer to BigThing
    // otherwise returns nullptr
    assert(bp);
}

void ListP::copyList(nodeP *node) {
    if(node != nullptr) {
        Object *o;
        copyList(node->next);
        o = node->value->clone(); // gives a deep copy
        insert(o);
    }
}