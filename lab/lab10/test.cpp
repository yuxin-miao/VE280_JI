/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 *
 * Correct Output:
 *
        12345678
        87654321
 *
 *
 */

#include <iostream>
#include "my_stack.h"
using namespace std;
int main()
{
    try{
        Stack<int> s1, s2;
        cout << s1.size() << endl;
        s1.push(4);
        s1.push(3);
        s1.push(2);
        s1.push(1);

        cout << s1.size() << endl;

        s2.push(7);
        s2.push(6);
        s2.push(5);
        s1.print();
        s2.print();
        cout << s2.size() << endl;


        Stack<int> s3 = s1 + s2;
        s3.print();
        cout << s3.size() << endl;

        s3 = s3 + 8;
        s3.print();
        cout << s3.size() << endl;


        reverse(s3);
        s3.print();
    }
    catch(stackEmpty){
        std::cout << "Oops, looks like I'm empty!\n";
    }
    return 0;
}
