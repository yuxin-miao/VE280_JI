#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
void print_array(int A[] , int n)
// EFFECTS: Print current array in the end so
// that smaller arrays are printed first
{
    for (int i = 0; i < n ; i++){
        if(i == n - 1)
            cout << A[i] << " ";
        else
            cout << A[i] << ", ";
    }
    cout << endl;
}

void print_triangle(int A[], int n) ; //EFFECTS: Sum triangle from array
int main() {
    // Read the input
    int number;
    int n = 0;
    stringstream temp;
    while (cin >> number) {
        n++;
        temp << number << " ";
    }
    int arr[n];
    for (int i = 0; i < n; i++) {
        temp >> number;
        arr[i] = number;
    }

    print_triangle(arr, n);
    return 0;
}

void print_triangle(int A[], int n) {
    // TODO
    if (n == 1) {
        print_array(A, n);
        return;
    }
    int arr_new[n - 1];
    for (int i = 0; i < n - 1; i++) {
        arr_new[i] = A[i] + A[i + 1];
    }
    print_triangle(arr_new, n - 1);
    print_array(A, n);
}