#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    string word;
    for (int i = 1; i < argc; i++) {
        word = argv[i]; // read every input word
        bool print = true;
        for (char & it : word) {
            // iterate, determine whether only contain alphabetic characters
            if (tolower(it) < 'a' || tolower(it) > 'z') {
                print = false;
                break;
            }
        }
        if (print) cout << word << " ";
    }
    return 0;
}
