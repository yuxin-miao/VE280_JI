#include <iostream>
#include <vector>
#include <limits>

int main(){
   std::vector<int> v(
         std::numeric_limits<unsigned short>::max(), 0);
   std::cout << std::numeric_limits<short>::max() << std::endl;
   std::cout << std::numeric_limits<unsigned short>::max() << std::endl;

   std::cout << "v[0]= " << v[0] << std::endl;

   short ssize = v.size();
   std::cout << "short size: " << ssize << std::endl;
   int isize = v.size();
   std::cout << "int size: " << isize << std::endl;

   vector<int>::size_type ix;
   for (ix = 0; ix != v.size(); ++ix) { // size_type
       cout << x[ix] << endl;
   }

   vector<int>::iterator mid = v.begin() + v.size()/2;

   // initializing with a range of elements
   vector<int> front(v.begin(), mid); // copy by iterator, not include mid
   vector<int> back(mid, v.end());
   int a[] = {1 ,2 ,3 ,4};
   unsigned int sz = sizeof(a) / sizeof(int);
   vector<int> va(a, a + sz); // a is a pointer
}
