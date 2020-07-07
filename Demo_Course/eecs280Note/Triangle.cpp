//
// Created by 于欣淼 on 2020/7/4.
//

#include "Triangle.h"

Triangle::Triangle()
        : a(1), b(1), c(1) {}
Triangle::Triangle(double a_in, double b_in, double c_in) : a(a_in), b(b_in), c(c_in) {//The constructor body is empty, since it has no further work to do.
    } // Constructor member-initializer list
    //The syntax is similar to declaring a member function, except:
    //• There is no return type.
    //• The name of the constructor is the same as the name of the class.
double Triangle::perimeter() const {
    return a + b + c;
}
void Triangle::scale(double s) { a *= s;
    b *= s;
    c *= s; }

