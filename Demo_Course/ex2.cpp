#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

void generate_strings(int K);
// EFFECTS: Given a integer K. Task is to print all binary string of size K without consecutive 1’s.
int main() {
    string input;
    getline(cin, input);
    int num;
    stringstream ss;
    ss << input;
    ss >> num;
    if (num > 0) generate_strings(num);
    return 0;
}

void print (const char str[], int size) {

    int i = 0;
    bool print = true;
    while (i < size - 1) {
        if (str[i] == '1' && str[i + 1] == '1') {
            print = false;
            break;
        }
        i++;
    }
    if (print) {
        i = size -1 ;
        while (i >= 0) {
            cout << str[i];
            i--;
        }
        cout << " ";
    }
}
void generate_strings_helper(char str[], int K, const int size) {

    if (K == 0) {
        print(str, size);
        return;
    }
    str[K - 1] = '0';
    generate_strings_helper(str, K - 1, size);
    str[K - 1] = '1';
    generate_strings_helper(str, K - 1, size);
}

void generate_strings(int K) {
    char *str = new(nothrow) char[K];

    generate_strings_helper(str, K, K);
    delete[] str;
}