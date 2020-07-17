//
// Created by cyx on 20-6-12.
//

#include <iostream>
#include "mylist.h"
using namespace std;
int main() {

    try{
        // possible case 1
        List<int> la;
        la.insertBack(9);
        List<int> ld;
        ld.insertBack(8);
        List<int> empty;
        /*for (long long int i = 0; i < 10000000; i++) {
            ld.insertBack(1);

        }*/

        List<int> le = Add(empty, empty);
        la.print();
        empty.print();
        le.print();
        cout << isLarger(empty, empty);
    }
    catch(emptyList){
        std::cout << "Remove from empty list!\n";
    }

    return 0;
}

