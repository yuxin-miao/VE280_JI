#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <list>
using namespace std;

class Base
{
public:
    virtual ~Base() = 0;
    virtual void DoSomething()
    {
        cout << "Do something in class Base!" << endl;
    };
};

class Derived : public Base
{
    int* pArr;
    int size;
public:
    Derived(); //Derived的构造函数
    ~Derived() override //Derived的析构函数
    {
       cout << "Output from the destructor of class Derived!" << endl;
     };
    void DoSomething() override
    {cout << "Do something in class Derived!" << endl;
    };
};

class subDerived : public Derived {
public:
    subDerived() {};
    ~subDerived()=default;
};
void add(double n1, double n2) {
    cout << n1 + n2;
}/*
class A{
    int i;
public:
    A(): i(0) {
        cout << "dc";
    }
    A(const A&a) {

    }
};
*/
class A {
public:
    virtual void f() = 0;
    virtual void g(){cout << "A::g" << endl;}
    void h(){ cout << "A::h" << endl;}
};
class B: public A{
public:
    void f() {cout << "B::f" << endl;}
    void g(){cout << "B::g" << endl;}
    virtual void h(){ cout << "B::h" << endl;}
};

class C: public B{
public:
    void f() {cout << "C::f" << endl;}
    void h(){ A::h();}
};
class D: public C{
public:
    void h(){ cout << "D::h" << endl;}
};
int main(){
    B* pa;
    B b;
    C c;
    D d;
    c.f();
    c.h();
    pa = &b;
    pa->f();
    pa->g();
    pa->h();

    pa = &c;
    pa->f();
    pa->g();
    pa->h();
    A&ra = d;
    ra.g();
    ra.h();
    d.f();
    d.g();

    list<int> l;
    for (int i = 0; i < 10; i++) {
        l.push_back(i);
    }


}/*
int main()
{


    Base *pt = new subDerived();
    delete pt;

    Derived *pTest1 = new Derived(); //Derived类的指针
    pTest1->DoSomething();
    delete pTest1;

    cout << endl;

    Base *pTest2 = new Derived(); //Base类的指针
    pTest2->DoSomething();
    delete pTest2;

    return 0;
}
*/