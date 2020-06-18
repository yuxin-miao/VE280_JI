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
    // get root through a, b, c
    root result;
    float delta = getB() * getB() - 4 * getA() * getC(); // determine the number of real roots through delta
    if (delta >= 0) {
        if (delta == 0) result.realRootNum = 1;
        else result.realRootNum = 2;
        float root1 = (- getB() - sqrtf(delta)) / (2 * getA());
        float root2 = (- getB() + sqrtf(delta)) / (2 * getA());
        result.roots[0].real = fminf(root1, root2); // for root[0] to have the smaller value
        result.roots[1].real = fmaxf(root1, root2);
        result.roots[0].imaginary = 0;
        result.roots[1].imaginary = 0;
    }
    else {
        result.realRootNum = 0;
        result.roots[0].real = (- getB()) / (2 * getA());
        result.roots[1].real = (- getB()) / (2 * getA());
        // ensure that roots[0] has smaller one
        result.roots[0].imaginary = fminf(-sqrtf(-delta) / (2 * getA()), sqrtf(-delta) / (2 * getA()));
        result.roots[1].imaginary = fmaxf(-sqrtf(-delta) / (2 * getA()), sqrtf(-delta) / (2 * getA()));

    }
    return result;
}

int quadraticFunction::intersect(quadraticFunction g){
    // TODO: implement this function
    if (a == g.getA()) {
        // determine whether they are parallel
        if (b == g.getB() && c != g.getC()) return 0;
        return 1;
    }
    // through delta of function (f - g), determine whether intersect
    float delta = (getB() - g.getB()) * (getB() - g.getB()) - 4 * (a - g.getA()) * (getC() - g.getC());
    const double eps = 1.0e-6;
    if (delta >= 0 || fabs(delta) < eps) return 1;
    else return 0;
}
