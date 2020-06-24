#include <sstream>
#include "vector.h"

Vector::Vector(double w, double q):w(w), q(d) {
}

Vector::Vector(Vector &v):w(v.w), q(v.q) {
}

double Vector::getX() {
   return w;
}

double Vector::getY() {
   return this->q;
}

Vector Vector::add(Vector &v) {
   return Vector(w+v.w, q+v.q);
}

void Vector::scale(double s) {
   return Vector(s*w, s*q);
}

double Vector::dot(Vector &v) {
   return w*v.w + q*v.q;
}

std::string toString() {
   ostringstream is; 
   is << "(" << w << ", " << q << ")";
   return is.str();
}
