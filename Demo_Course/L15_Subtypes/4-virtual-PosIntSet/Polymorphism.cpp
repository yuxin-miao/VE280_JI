/*
  ad hoc polymorphism, which refers to function overloading
  parametric polymorphism in the form of templates
  subtype polymorphism, which allows a derived-class object to be used where a base-class object is expected
 */

/**Function Overloading**/
class OverBase {
public:
    void foo(int a);
    int foo(string b);
};
class Person {
public:
    void greet();
    void greet(int x); // OK
    void greet(string x); // OK
    void greet(int x, string s); // OK
    void greet(string s, int x); // OK
    //bool greet(); // ERROR: signature the same as the first overload

    void greet() const; // OK: implicit this parameter different
    // changes the implicit 'this' parameter from being a pointer to non-const to a pointer to const
};

/***Subtype**/
class Top {
public:
    int f1() const {
        return 1;
    }
    virtual int f2() const {
        return 2;
    }
};
class Middle : public Top {
public:
    int f1() const {
        return 3;
    }
    virtual int f2() const {
        return 4;
    }
};
class Bottom : public Middle {
public:
    int f1() const {
        return 5;
    }
    virtual int f2() const {
        return 6;
    } };

int main() {
    Base b;
    b.foo(42);
    b.foo("test");

    Top top;
    Middle mid;
    Bottom bot;
    Top *top_ptr = &bot;
    Middle *mid_ptr = &mid;
    //no indirection in the calls top.f1() and mid.f1()
    cout << top.f2() << endl; // 2
    cout << mid.f1() << endl; // 3
    cout << top_ptr->f1() << endl; // 1
    cout << top_ptr->f2() << endl; // 6
    cout << mid_ptr->f2() << endl; // 4
    mid_ptr = &bot;
    cout << mid_ptr->f1() << endl; // 3
    cout << mid_ptr->f2() << endl; // 6

}
/*
 *
With subtype polymorphism, we end up with two use cases for inheritance:
• implementation inheritance, where a derived class inherits functionality from a base class
• interface inheritance, where a derived class inherits the interface of its base class, but not necessarily any implementation

 */