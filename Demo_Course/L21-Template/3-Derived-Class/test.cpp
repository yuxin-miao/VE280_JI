#include <iostream>
using namespace std;

class A{
   int a=0;
   int b=1;
public:
   virtual void print() const{
       cout << "class A print" << endl;
      cout << a << " " << b << endl;
   }
};

class B: public A{
   int c=2;
public:
   void print() const{
       cout << "class B print" << endl;
      A::print();
      cout << c << endl;
   }
};

int main(){
   A a;
   a.print();

   B b;
   b.print();
   cout << "ab: " << endl;
   A ab=b;
   ab.print();
   cout << "*pa: " << endl;
   A *pa = &b;
   pa->print();

   return 0;
}
