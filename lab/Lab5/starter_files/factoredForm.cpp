//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in){
    a = a_in;
    float delta = b_in * b_in - 4 * a_in * c_in;
    r1.imaginary = 0; r1.real = 0; r2.imaginary = 0; r2.real = 0;
    if (delta >= 0) {

        r1.real = (-b_in - sqrtf(delta)) / (2 * a_in); r1.imaginary = 0;
        r2.real = (-b_in + sqrtf(delta)) / (2 * a_in); r2.imaginary = 0;
    }
    else {

        r1.real = -b_in / (2 * a_in); r1.imaginary = - sqrtf(-delta) / (2 * a_in);
        r2.real = -b_in / (2 * a_in); r2.imaginary = sqrtf(-delta) / (2 * a_in);
    }

}
// TODO: implement this constructor

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    // TODO: implement this function
    return - a * (r1.real + r2.real);
}

float quadraticFunction::getC() const {
    // TODO: implement this function
    return a * (r1.real * r2.real - r1.imaginary * r2.imaginary);
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return a * x * x + getB() * x + getC();
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    root result;
    if (r1.imaginary == 0) {
        if (r1.real == r2.real)
            result.realRootNum = 1;
        else
            result.realRootNum = 2;
    }
    else
        result.realRootNum = 0;

    result.roots[0].real = fminf(r1.real, r2.real); result.roots[0].imaginary = fminf(r1.imaginary, r2.imaginary);
    result.roots[1].real = fmaxf(r1.real, r2.real); result.roots[1].imaginary = fmaxf(r1.imaginary, r2.imaginary);
    return result;
}

int quadraticFunction::intersect(quadraticFunction g) {
    // TODO: implement this function
    if (a == g.getA()) return 1;

    float delta = (getB() - g.getB()) * (getB() - g.getB()) - 4 * (a - g.getA()) * (getC() - g.getC());
    const double eps = 1.0e-6;
    if (delta >= 0 || fabs(delta) < eps) return 1;
    else return 0;
}