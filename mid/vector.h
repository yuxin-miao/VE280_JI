#ifndef Vector_h
#define Vector_h
class Vector {
   double w;
   double q;
public:
   explicit Vector(double w=0, double q=0);
   Vector(Vector &v);

   double getX();
   double getY();

   Vector add(Vector &v);
   Vector scale(double s);
   double dot(Vector &v);
   std::string toString();   
};
#endif
