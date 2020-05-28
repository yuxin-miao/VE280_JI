#include <iostream>
using namespace std;

int min(int x, int y){
    if (x < y){
        return x;
    } else{
        return y;
    }
}

int max(int x, int y){
    if (x < y){
        return y;
    } else{
        return x;
    }
}
int f1() {
    return 1;
}

int f2() {
    return 2;
}
void call_stack_usingPointer ();
void function_pointer();
typedef int (*fptr)();
typedef int (* fpTR)(int, int);
fptr f( char c ) {
    if ( c == '1' ) {
        return f1; // how to return a function pointer
    }
    else {
        return f2;
    }
}
fpTR fp_return() {
    return min;
}; 
int main(){
    //function_pointer();

    call_stack_usingPointer();
    return 0;
}

void add_one(int *x) {
    // MODIFIES: variable pointed by x, *x
    // Effects: add one to *x
    *x = *x + 1;
}
void call_stack_usingPointer () {
    int foo = 2;
    int *bar = &foo;
    /*
     * In the stack of call_stack_usingPointer, memory: foo (store number 2) & bar (pointing to foo)
     * When call add_one, another stack, memory: x (also pointing to foo !!)
     */
    add_one(bar);
    cout << foo << endl;
}
void function_pointer() {
    int (* fp)(int, int) = min;
    int (* fpArray[])(int, int) = {min, max}; // rvalue, could not be incremented
    int (** fpp)(int, int) = fpArray;
    cout << fp(1, 2) << endl;
    cout << fpArray[0](2, 3) << endl;
    cout << fpArray[1](3, 4) << endl;
    // fp++;  Arithmetic on a pointer to the function type 'int (int, int)'
    // fpArray++; Cannot increment value of type 'int (*[2])(int, int)'
    fpp++;
    cout << (*fpp)(4, 5) << endl;
    cout << (void *)fp << endl;
    cout << fp << endl;
}
