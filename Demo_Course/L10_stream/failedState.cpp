#include <iostream>
using namespace std;

int main(){
    int foo;
    double bar;
    string baz;
    cout << "Enter an integer: ";
    cin >> foo;
    while (!cin){
        cout << "Enter an integer: ";
        cin.clear(); // Notice the clear, or cin will be in the failed state
        // and could not receive input again
        cin.ignore (100, '\n');
        cin >> foo;
    }

    cout << "Enter a double: ";
    cin >> bar;
    while (!cin){
        cout << "Enter a double: ";
        cin.clear();
        cin.ignore (100, '\n');
        cin >> bar;
    }

    cout << foo << " " << bar << endl;

    return 0;
}
