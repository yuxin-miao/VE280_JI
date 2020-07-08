#include <iostream>

class M { public:
    M(const string &s) : mstr(s) {
        cout << "M ctor: " << mstr << endl;
    }
    ~M() {
        cout << "M dtor: " << mstr << endl;
    }
private: string mstr;
};

class C {
public:
    C(const string &s) : cstr(s), m1(s + ".m1"), m2(s + ".m2") {
        cout << "C ctor: " << cstr << endl;
    }
    ~C() {
        cout << "C dtor: " << cstr << endl;
    }
private:
    string cstr;
    M m1;
    M m2;
};
int main() {
    C c1("c1");
    C *cptr = new C("(*cptr)");
    C c2("c2");
    delete cptr;
}