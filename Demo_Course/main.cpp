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

int main(){
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
    return 0;
}
