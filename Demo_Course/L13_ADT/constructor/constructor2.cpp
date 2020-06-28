#include <iostream>
using namespace std;

class C{

public:
   C(){
      cout << "Constructor of C" << endl;
   };
};

class D{
   C c;

public:
   D(C x){ // 先调用默认构造函数
       /*
        *    C(){
      cout << "Constructor of C" << endl;
        */
      c = x;
   };
};

int main(){
   C c;
   cout << "after c" << endl;
   D d(c);

   return 0;
}

