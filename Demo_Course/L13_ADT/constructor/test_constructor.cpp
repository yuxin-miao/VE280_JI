#include <iostream>
using namespace std;

class Test1
{
public:
    Test1() // 无参构造函数
    {cout << "Construct Test1" << endl ;}
    Test1(const Test1& t1) // 拷贝构造函数
    {cout << "Copy constructor for Test1" << endl ;this->a = t1.a ;}
    Test1& operator = (const Test1& t1) // 赋值运算符
    {cout << "assignment for Test1" << endl ;this->a = t1.a ;return *this;}
    int a ;
};
class Test2
{
public:
    Test1 test1 ;
    Test2(Test1 &t1)
    {test1 = t1 ;}
};
class Test3
{
public:
    Test1 test1 ;
    Test3(Test1 &t1):test1(t1){}
};
