//
// Created by 于欣淼 on 2020/7/4.
//

#ifndef EECS280NOTE_TRIANGLE_H
#define EECS280NOTE_TRIANGLE_H


class Triangle {
    double a;
    double b;
    double c;
public:
    // default constructor
    Triangle();
    // EFFECTS: Initializes this to be an equilateral triangle with // the given side length.
    Triangle(double side_in)
            : Triangle(a_in, b_in, c_in) {} // delegate to 3-argument constructor
            // The delegation must be in the member-initializer list. or a new, temporary object would be created then thrown away

    Triangle(double a_in, double b_in, double c_in);

     // EFFECTS: Returns the perimeter of this triangle.
    double perimeter() const;
    double set_side1(double a);
    void scale(double s);
private:
        void check_invariants() {
        assert(0 < a && 0 < b && 0 < c);
        assert(a+b>c &&a+c>b&&b+c>a);
    }
};


#endif //EECS280NOTE_TRIANGLE_H
