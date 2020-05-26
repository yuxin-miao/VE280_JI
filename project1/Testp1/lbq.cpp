#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

bool is_valid(int number, int test);
bool Triangle_test(int number);
bool Palindrome_test(int number);
bool Power_test(int number);
bool Abundant_test(int number);


int main() {
    int number = 0;     // the first input
    int test = 0;       // the second input
    bool flag = false;          // the variable for deciding whether to print 1 or 0
    cout << "Please enter the integer and the test number: ";
    cin >> number >> test;
    while (!is_valid(number, test)) {
        cout << "Please enter the integer and the test number: ";
        cin >> number >> test;
    }
    switch (test)       // choose the type of test
    {
    case 1:
        flag=Triangle_test(number);
        break;
    case 2:
        flag=Palindrome_test(number);
        break;
    case 3:
        flag=Power_test(number);
        break;
    case 4:
        flag=Abundant_test(number);
        break;
    default:
        break;
    }
    // print the result
    if (flag) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }
    return 0;
}    
// test whether the input is valid for this program 
bool is_valid(int number, int test){
    if (number > 10000000 || number <= 0 || test > 4 || test < 1) {
        return false;       
    }
    return true;
}
// test if the number is a Triangle number
bool Triangle_test(int number) {
    for (int n = 0; n <= number; n++) {
        if (number == n * (n + 1) / 2) {
            return true;
        }
    }
    return false;
}
// test if the number is a Palindrome number
bool Palindrome_test(int number) {
    string num_str = to_string(number);
    int length = num_str.length();
    for (int i = 0; i < length; i++){
        if (num_str[i] != num_str[length - 1 - i]) {
            return false;
        }
    }
    return true;
}
// test if the number is a Power number
bool Power_test(int number) {
    for (int m = 2; m * m <= number; m++) {
        for (int n = 2; n <= log2(number); n++) {
            if (pow(m,n) == number) {
                return true;
            }
        }
    }
    return false;
}
// test if the number is a Abundant number
bool Abundant_test(int number) {
    int sum_of_factorization = 0;    // calculate the sum of the prime factorization 
    for (int i = 2; i < number; i++) {
        if (number % i == 0) {
            sum_of_factorization += i;
        }
    }
    if (sum_of_factorization > number) {
        return true;
    }
    else {
        return false;
    }
}

