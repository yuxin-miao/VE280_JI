#include <iostream>
using namespace std;
void Reference_address();
void Pointer_address();
int Array_address(int x[]);

// Const Qualifier - used for compiler to to prevent from changing the value
void Const_reference(int iVal); // const-qualification of parameters only has an effect in function definition
void Const_pointer(int num);

int main() {
    //Reference_address();
    //Pointer_address();
    int arr_num[9] = {2, 3};
    //cout << Array_address(arr_num)<< " x[0]: " << arr_num[0] << endl;
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

int Array_address(int x[]){
    /* Array - passed by reference
     * array = &array[0]
     * change the value of array[0], will remain out of the function
     */
    cout << "Original x[0]:" << x[0] << endl;
    x[0] = 10;
    return x[0];
}

void Const_reference(int iVal) {
    const int &rVal = iVal;
    const int &ref = iVal + 10; // OK to initialized to a rvalue
    const int &ref2 = 10; // OK to initialized to a rvalue
    /*
     * For nonconst reference, could not initialized to a rvalue
     * **WRONG** - int &ref = 10;
     */
    iVal = 9;  // Can change the value, but can't change it through const reference rVal

}

void Const_pointer(int num) {
    const int *p1 = &num; // can't change the value of num by pointer p1
    int *const p2 = &num; // can't change the pointer p2
    const int *const p3 = &num; // combination of p1, p2, both can't be changed
    int x = 10;
    num = 5; // num is not const, can be changed directly
    p1 = &x; // **WRONG** - p2 = &x;
    *p2 = 8; // **WRONG** - *p1 = 8;
}
