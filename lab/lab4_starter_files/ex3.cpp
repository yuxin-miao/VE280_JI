#include <iostream>
#include <sstream>
using namespace std;

int main () {
    string input;
    getline(cin, input);
    stringstream ss(input);
    string out;
    int num = 0;
    while(getline(ss, out, ',')) {
        int length = out.length();
        for (int i = length - 1; i >= 0; --i) {
            if (out.at(i) == ' ')
                out.erase(i, 1);
        }
        cout << out << endl;
        num++;
    }
    cout << num << endl;
}


