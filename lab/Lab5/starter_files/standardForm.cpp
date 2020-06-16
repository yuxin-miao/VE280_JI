//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in){
    a = a_in;
    b = b_in;
    c = c_in;
}
// TODO: implement this constructor

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
    return getA() * x * x + getB() * x + getC();
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    root result;
    float delta = getB() * getB() - 4 * getA() * getC();
    if (delta >= 0) {
        if (delta == 0) result.realRootNum = 1;
        else result.realRootNum = 2;
        float root1 = (- getB() - sqrtf(delta)) / (2 * getA());
        float root2 = (- getB() + sqrtf(delta)) / (2 * getA());
        if (root1 > root2) {
            result.roots[0].real = root2;
            result.roots[1].real = root1;
        }
        else {
            result.roots[0].real = root1;
            result.roots[1].real = root2;
        }
        result.roots[0].imaginary = 0;
        result.roots[1].imaginary = 0;
    }
    else {
        result.realRootNum = 0;
        result.roots[0].real = (- getB()) / (2 * getA());
        result.roots[1].real = (- getB()) / (2 * getA());
        if (getA() > 0) {
            result.roots[0].imaginary = -sqrtf(-delta) / (2 * getA());
            result.roots[1].imaginary = sqrtf(-delta) / (2 * getA());
        }
        if (getA() < 0) {
            result.roots[0].imaginary = sqrtf(-delta) / (2 * getA());
            result.roots[1].imaginary = -sqrtf(-delta) / (2 * getA());
        }
    }
    return result;
}

int quadraticFunction::intersect(quadraticFunction g){
    // TODO: implement this function
    if (a == g.getA()) return 1;
    float delta = (getB() - g.getB()) * (getB() - g.getB()) - 4 * (a - g.getA()) * (getC() - g.getC());
    const double eps = 1.0e-6;
    if (delta >= 0 || fabs(delta) < eps) return 1;
    else return 0;
}
