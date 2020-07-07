#include <iostream>
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
