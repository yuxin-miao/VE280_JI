#include <iostream>
#include "dlist.h"
using namespace std;
bool (*compare) (const int*, const int*);
bool larger(const int* x, const int* y) {
    return *x > *y;
}
int main(int argc, char *argv[])
{
    try {
        Dlist<int> ilist;
        int *ip = new int(1);
        int *ip2 = new int(2);
        int *ip3 = new int(3);

        ilist.print();
        ilist.insertFront(ip);
        ilist.insertFront(ip2);
        ilist.insertBack(ip3);

        ilist.print();

        compare = larger;
        int* val = ilist.remove(compare, ip2);
        delete val;
        int* val2 = ilist.remove(compare, ip2);
        delete val2;
        ilist.print();
        for (int i = 5; i< 10; i++) {
            ilist.insertBack(new int(i));
        }

        int *remove = ilist.removeFront();
        delete remove;
        ilist.print();
    }
    catch (emptyList) {
        cout << "the list is empty!" << endl;
    }
    return 0;
}
