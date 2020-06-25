//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in){
    // TODO: implement this constructor
    a = a_in;
    b = b_in;
    c = c_in;
}

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    return b;
}

float quadraticFunction::getC() const {
    return c;
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return a*x*x+b*x+c;
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    // EFFECTS: returns the roots of the quadratic function
    float delta;
    float buffer = a; //store the absolute value of a
    if (a < 0) buffer = -a; // get the absolute value of a
    root root_1;
    delta = b*b-4*a*c;
    if (delta > 0){ // if two real root
        root_1.realRootNum = 2;
        root_1.roots[0].real = -b / (2 * a) - sqrtf(delta) / (2 * buffer);
        root_1.roots[0].imaginary = 0;
        root_1.roots[1].real = -b / (2 * a) + sqrtf(delta) / (2 * buffer);
        root_1.roots[1].imaginary = 0;
    }
    else if (delta == 0){ // if one real root
        root_1.realRootNum = 1;
        root_1.roots[0].real = -b / (2 * a);
        root_1.roots[0].imaginary = 0;
        root_1.roots[1].real = -b / (2 * a);
        root_1.roots[1].imaginary = 0;
    }
    else if (delta < 0){ // if no real root
        root_1.realRootNum = 0;
        root_1.roots[0].real = -b / (2 * a);
        root_1.roots[0].imaginary = - sqrtf(-delta) / (2 * buffer);
        root_1.roots[1].real = -b / (2 * a);
        root_1.roots[1].imaginary = sqrtf(-delta) / (2 * buffer);
    }
    return root_1;
}

int quadraticFunction::intersect(quadraticFunction g){
    // TODO: implement this function
    // EFFECTS: returns whether g and this intersect
    // if true, return 1
    // if false, return 0
    if (a != g.getA()) { // if the a of two functions are different, i.e: f.a - g.a != 0
        quadraticFunction func(a - g.getA(), b - g.getB(), c - g.getC());// turn f(x) = g(x) into f(x) - g(x) = 0
        root root1;
        root1 = func.getRoot();
        return root1.realRootNum != 0; // if no realroot, return 0;
    }
    else { // if the a of two functions are the same
        if (b == g.getB() && c != g.getC()){ // if two lines are parallel
            return 0;
        }
        else {
            return 1;
        }
    }
}