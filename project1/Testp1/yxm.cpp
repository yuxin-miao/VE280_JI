#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;
int Check_input(int& num, int& test) {
    // Effects: Test the validity of the input And ask for a valid input
    if (num <= 0 || num > 1000000 || test > 4 || test < 1) {
        cout << "Please enter the integer and the test number: ";
        cin >> num >> test;
        Check_input(num, test);
    }
    else return 0;
    return 0;
}

bool triangle (int x);
bool palindrome (int x, int &pre_digit);
bool power (int x);
bool abundant (int x);

int main() {
    // Receive input
    cout << "Please enter the integer and the test number: ";
    int num, test;
    cin >> num >> test;
    Check_input(num, test);
    int pre_digit = 0;
    // Do the test
    switch (test) {
        case 1:
            cout << triangle(num) << endl;
            break;
        case 2:
            cout << palindrome(num, pre_digit) << endl;
            break;
        case 3:
            cout << power(num) << endl;
            break;
        case 4: {
            cout << abundant(num) << endl;
            break;
        }
        default:
            cout << "What's wrong?" << endl;
            break;
    }
    return 0;
}

bool triangle (int x) {
    // Effects: Test whether it is a triangle number

    for (int n = 1 ; n < 1450 ; n++) {
        if (x == n * (n + 1) / 2) {
            return true;
        }
        else if (2 * x < n * n) return false;
    }
    return false;
}

bool palindrome (int x, int &pre_digit) {
    // Effects: Test whether it is a palindrome
    if (x < 10)  {
        pre_digit++;
        return true;
    }
    int result = 0, y = 10, n = x, temp = 1;
    while (x > 0) {
        temp = x % y;
        result = result * 10 + temp / (y / 10);
        y = y * 10;
        x = x - temp;
        pre_digit++;
    }
    return result == n;
}

bool power (int x) {
    // Effects: Test whether it is a power number
    if (x == 1) return true;
    for (int m = 2; m < 1001; m++) {
        for (int n = 2; x >= pow(m, n); n++) {
            if (x == pow(m, n)) return true;
        }
    }
    return false;
}

bool abundant (int x) {
    // Effects: Test whether it is an abundant number
    int result = 0;
    for (int n = 1; n < x; n++) {
        if ( x % n == 0) result += n;
    }
    return result > x;
}
