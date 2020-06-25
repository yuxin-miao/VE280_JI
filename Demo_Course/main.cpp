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
int try_arr (int arr[], int& index) {

    return arr[index++];
}
void dynamic_size_array() {
    // Request block of memory of size n
    int n = 5;
    int *q = new(nothrow) int[n];

    if (!q)
        cout << "allocation of memory failed\n";
    else
    {
        for (int i = 0; i < n; i++)
            q[i] = i+1;

        cout << "Value store in block of memory: ";
        for (int i = 0; i < n; i++)
            cout << q[i] << " ";
    }

    // freed the block of allocated memory
    delete[] q;
}
void print_triangle(int A[], int size) ; //EFFECTS: Sum triangle from array
int main() {/*
    // Read the input
    int number;
    int size = 0;
    string line;
    getline(cin, line);
    stringstream temp;
    temp << line;
    while ( temp >> number) {
        size++;
    }
    stringstream ss;
    ss << line;
    int *arr = new(nothrow) int[size];
    for (int i = 0; i < size; i++) {
        ss >> number;
        arr[i] = number;
    }

    print_triangle(arr, size);
    delete[] arr;*/
    int arr_try[5];
    for (int i = 0; i < 5; i++) {
        arr_try[i] = i;
    }
    int index = 0;
    for (int i = 0; i < 5; i++) {
        cout << "before " << index << endl;
        cout << try_arr(arr_try, index) << endl;
        cout << "after " << index << endl;

    }


    return 0;
}

void print_triangle(int A[], int size) {
    // TODO
    if (size == 1) {
        print_array(A, size);
        return;
    }
    int *arr_new = new(nothrow) int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        arr_new[i] = A[i] + A[i + 1];
    }
    print_triangle(arr_new, size - 1);
    print_array(A, size);
    delete [] arr_new;
}