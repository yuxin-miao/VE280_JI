//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in){
    // TODO: implement this constructor
    // EFFECTS: calculate r1 and r2 based on b_in, c_in and a;
    //          r1 is the smaller root
    a = a_in;
    float delta;
    float buffer = a; //store the absolute value of a
    if (a < 0) buffer = -a; // get the absolute value of a
    delta = b_in*b_in-4*a*c_in;
    if (delta > 0){ // if two real root
        r1.real = -b_in / (2 * a) - sqrtf(delta) / (2 * buffer);
        r1.imaginary = 0;
        r2.real = -b_in / (2 * a) + sqrtf(delta) / (2 * buffer);
        r2.imaginary = 0;
    }
    else if (delta == 0){ // if one real root
        r1.real = -b_in / (2 * a);
        r1.imaginary = 0;
        r2.real = -b_in / (2 * a);
        r2.imaginary = 0;
    }
    else if (delta < 0){ // if no real root
        r1.real = -b_in / (2 * a);
        r1.imaginary = - sqrtf(-delta) / (2 * buffer);
        r2.real = -b_in / (2 * a);
        r2.imaginary = sqrtf(-delta) / (2 * buffer);
    }
}

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    // TODO: implement this function
    return -r1.real * a - r2.real * a; // return -a * (r1 + r2)
}

float quadraticFunction::getC() const {
    // TODO: implement this function
    return a * (r1.real * r2.real - r1.imaginary * r2.imaginary);  // return a*r1*r2
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return a*x*x+ getB()*x + getC();
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    // EFFECTS: returns the roots of the quadratic function
    root root1;
    root1.roots[0] = r1;
    root1.roots[1] = r2;
    if (r1.real == r2.real && r1.imaginary == 0 && r2.imaginary == 0){ // if one repeated real solution
        root1.realRootNum = 1;
    }
    else if (r1.imaginary != 0 && r2.imaginary != 0){ // if two imaginary solutions
        root1.realRootNum = 0;
    }
    else if (r1.real != r2.real && r1.imaginary == 0 && r2.imaginary == 0){ // if two real solutions
        root1.realRootNum = 2;
    }
    return root1;
}

int quadraticFunction::intersect(quadraticFunction g) {
    // TODO: implement this function
    // EFFECTS: returns whether g and this intersect
    // if true, return 1
    // if false, return 0
    if (a != g.getA()) { // if the a of two functions are different, i.e: f.a - g.a != 0
        quadraticFunction func(a - g.getA(), getB() - g.getB(), getC() - g.getC());
        root root1;
        root1 = func.getRoot();
        return root1.realRootNum != 0; // if no realroot, return 0;
    }
    else { // if the a of two functions are the same
        if (getB() == g.getB() && getC() != g.getC()){ // if two lines are parallel
            return 0;
        }
        else {
            return 1;
        }
    }
}