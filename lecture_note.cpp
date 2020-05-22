#include <iostream>
using namespace std;
void Reference_address();
void Pointer_address();

int main() {
    Reference_address();
    Pointer_address();
    return 0;
}


void Reference_address() {
    /* Reference - could be considered as an alias for this object
     * reference r would occupy the same memory as x
     * change r same to change (r and x)
     */
    int x = 0; int &r = x; int y = 1;
    r = y; r = 2;
    cout << "Reference r: x = " << x << " y = " << y << " r = " << r << endl;
}

void Pointer_address() {
    /* Pointer - occupy another memory, store the address of the object it is pointing to
     * At first p is the address of x, and then changed to store the address y
     */
    int x = 0; int *p = &x; int y = 1;
    p = &y; *p = 2;
    cout << "Pointer p: x = " << x << " y = " << y << " *p = " << *p << endl;
}