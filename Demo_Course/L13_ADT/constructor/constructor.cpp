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
   D(C x):c(x){ // 直接调用构造函数 没有调用默认构造函数
   };
};

int main(){
   C c;
   cout << "after c" << endl;
   D d(c);

   return 0;
}

