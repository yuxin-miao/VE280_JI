//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-25.
//

#include <iostream>

#include "course.h"

int main() {

    Course *ve281 = create("Technical", "VE281", false, 0);

    try{


        ve281->updateTask("Lab", 1, 9, 23);
        ve281->updateTask("Project", 1, 9, 30);
        ve281->updateTask("Project", 1, 10, 4);
        ve281->print();

    }
    catch(tooManyTasks){
        std::cout << "Too many tasks\n";
    }

    delete ve281;


    return 0;
}

