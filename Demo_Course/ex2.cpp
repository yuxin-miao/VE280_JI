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
void binary_add (int arr[], int K) {
    int carry = 1;
    int x = arr[0];
    int y = arr[1];
    int z  = arr[2];

    for (int i = K - 1; i >= 0; i --){
        if (arr[i] == 0) {
            arr[i] += carry;
            carry = 0;
        }
        else if (arr[i] == 1){
            arr[i] = 0;
            carry = 1;
        }
        else {cout << "wrong " << endl;}
        if (carry == 0) break;
    }
}
void generate_strings_helper(int arr[], int K) {
    for (int i = 0; i < pow(2, K) - 1; i++) {
        bool print = true;
        binary_add(arr, K);

        for (int j = 0; j < K; j++) {
            if ((arr[j] == 1) && (arr[j + 1] == 1)) {
                print = false;
                break;
            }
        }
        if (print) {
            for (int j = 0; j < K; j++) {
                cout << arr[j];
            }
            cout << " ";
        }
    }
}
void generate_strings(int K) {
    int arr[K];
    for (int i = 0; i < K; i++) {
        arr[i] = 0;
    }
    for (int j = 0; j < K; j++) {
        cout << arr[j];
    }
    cout << " ";
    generate_strings_helper(arr, K);
}