//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-25.
//

#include <iostream>

#include "course.h"

int main() {

    Course *ve281 = create("Technical", "VE281", false, 0);
    Course *ve370 = create("Upper Level Technical", "VE370", false, 0);
    Course *ve482 = create("Upper Level Technical", "VE482", true, 10);
    Course *ve492 = create("Upper Level Technical", "VE492", true, 10);


    try{
        ve482->updateTask("Homework", 1, 9, 20);
        ve482->updateTask("Lab", 1, 9, 15);
        ve482->updateTask("Lab", 2, 9, 15);
        ve482->updateTask("Lab", 3, 9, 20);
        ve482->updateTask("Lab", 4, 9, 15);

        ve482->print();
        ve482->updateTask("Lab", 4, 8, 15);
        ve482->updateTask("Lab", 3, 9, 20);

        ve482->print();

    }
    catch(tooManyTasks){
        std::cout << "Too many tasks\n";
    }

    delete ve281;
    delete ve370;
    delete ve482;
    delete ve492;


    return 0;
}

