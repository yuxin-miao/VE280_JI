#include <iostream>

using namespace std;

class Complex{
   double real;
   double img;

public:
   Complex(double real=0, double img=0): 
      real(real), img(img){}
   Complex operator      +(const Complex &c){ // defined inside
      return Complex(this->real + c.real, 
                     this->img + c.img);
   }
   void print(){
      cout << this->real << "+" 
            << this->img << "i" << endl;
   }

   friend Complex operator-(const Complex &,  // since it is defined outside the class
                            const Complex &); // keyword friend needed
                            // or it could not access the private member
                            // not a member function, but an ordinary function
};

Complex operator  -(const Complex &c1, 
                    const Complex &c2){
   return Complex(c1.real - c2.real, c1.img - c2.img);
}

int main(){
   Complex c(3, 2);
   c.print();

   Complex c2 = c + c;
   c2.print();

   (c2 - c).print();
}
