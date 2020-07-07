class BaseLookUp {
    int fooo; // this value could not be accessed in derived class directly
protected:
    int age; // then this value could be used in Derived class, but not to the outside world
public:
    int x;
    void foo (const string &s);
};
class DerivedLook : public BaseLookUp {
public:
    void x();
    void foo (int i);
};

int main {
    DerivedLook d;
    // int a = d.x; // error, will only find member function x in DerivedLook, not int x in Base
    // d.foo("hello") // error
    return 0;
};