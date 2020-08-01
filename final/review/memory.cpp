#include <iostream>
class Base {
protected:
    int *p;
public:
    Base() : p(new int(10)) {}
    ~Base() {delete p;}
};

class Derived : public Base {
    int *q;
public:
    Derived() : Base(), q(new int(20)) {}
    ~Derived() {delete q;}
};


int main() {
    /* A */
    Base* ptrA = new Derived;
    delete ptrA;// only calling the base destructor

    /* B */
    Derived* ptrB = new Derived;
    delete ptrB; // call the two constructor
}

