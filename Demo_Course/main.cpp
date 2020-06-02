#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <thread>

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
void enum_type();
void buffer_output();
void file_stream();
int main(){
    //function_pointer();
    //call_stack_usingPointer();
    int arr[] = {1, 2, 0, 4, 5};
    int i = 0;
    while (i < sizeof(arr)/ sizeof(arr[0])) {
        i++;
    }
    int x;
    string s1, s2;
    file_stream();


    getline(cin, s1);

    //enum_type();
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
    // fp++;  Arithmetic on a pointer to the function type 'int (int, int)' // doesn't make sense, what does it point to after inc?
    // fpArray++; Cannot increment value of type 'int (*[2])(int, int)'  // arrays are rvalues
    fpp++;
    cout << (*fpp)(4, 5) << endl;
    cout << (void *)fp << endl;
    cout << fp << endl;
}

// ENUMERATION TYPE
enum Suit_t {CLUBS, DIAMONDS, HEARTS, SPADES};
// automatically convert to int
// numerically, CLUBS = 0; DIAMONDS = 1; HEARTS = 2; SPADES = 3
void enum_type() {
    enum Suit_t s = CLUBS;
    const string suitname[] = {"clubs", "diamonds", "hearts", "spades"};
    Suit_t c;
    if (HEARTS == 2*DIAMONDS) {
    // refer the suit_t type as int
    }
    cout << "Suit is " << suitname[s] << endl;
}
// Enum is the type. An enumerator is one value of that type. 
// Enum is represented by an int, so an enumerator takes the same amount of space as an int value.
bool isRed(enum Suit_t s) {
    switch (s) {
        case DIAMONDS: cout << 1;
            break;
        case HEARTS: return true;
            break;
        case CLUBS: cout << 0;
            break;
        case SPADES: return false;
            break;
        default:
            assert(0);
            break;
    }
}
void buffer_output() {
    cout << "WELCOME!" << endl;
    cout << "Let's sleep";
}
void file_stream() {
    // READ: User data
    ifstream read_username;
    read_username.open("username");
    string user_dir;
    string user[30];
    int count_user = 0;
    cout << 0 << endl;

    if (read_username.is_open()) {

        getline(read_username, user_dir);
        string user_name;
        for (int i =0; getline(read_username, user_name); i++) {
            user[i] =  user_name;

            count_user++;
        }
        read_username.close();
    }
}