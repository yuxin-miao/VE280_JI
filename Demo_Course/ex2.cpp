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
void print (int arr[], int size) {

    int i = 0;
    bool print = true;
    while (i < size - 1) {
        if (arr[i] && arr[i + 1]) {
            print = false;
            break;
        }
        i++;
    }
    if (print) {
        i = 0;
        while (i < 3) {
            cout << arr[i];
            i++;
        }
        cout << " ";
    }
}
void generate_strings_helper(int arr[],int K, const int size) {
    int i = 0;
    int result = 0;
    while (i < size) {
        result += arr[i];
        i++;
    }
    if (result == size) return;
    if (arr[K - 1] == 0) {
        arr[K - 1] = 1;
        print(arr, size);
        generate_strings_helper(arr, K, size);
    }
    else if (arr[K - 1] == 1){
        arr[K - 1] = 0;
        print(arr, size);
        generate_strings_helper(arr, K - 1, size);
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
    generate_strings_helper(arr, K, K);
}