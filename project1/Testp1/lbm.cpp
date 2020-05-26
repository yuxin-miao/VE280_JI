#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;

//compare input with all triangle numbers smaller/equal than input
bool isTriangleNumber(int num){
    for (int i = 0; i*(i+1) <= 2*num; i++) {
        if (num == i*(i+1)/2) {
            return true;
        }
    }
    return false;
}

//compare the flipped input with original input
bool isPalindrome(int num){
    int storage = num;
    int flip = 0;
    //flip
    while (storage > 0){
        flip = flip*10 + storage%10;
        storage /= 10;
    }
    return flip == num;
}

//compare input with all power number smaller/equal than input
bool isPowerNumber(int num){
    //1 is a special power number
    if (num == 1){
        return true;
    }
    else {
        for (int i = 2; i * i <= num; i++) {
            for (int j = 2; pow(double(i), double(j)) - num <= 0; j++) {
                if (num == pow(double(i),double(j))) {
                    return true;
                }
            }
        }
    }
    return false;
}

//find all the proper divisor and get their sum
bool isAbundantNumber(int num){
    int sum = 0;
    for (int i = 1; i <= num/2; i++){
        if (num%i == 0){
            sum += i;
        }
    }
    return sum > num;
}

int main() {
    int num, test;
    while(true) {
        cout << "Please enter the integer and the test number: ";
        cin >> num >> test;
        if (num > 0 && test >= 1 && test <= 4){
            break;
        }
    }
    if (test == 1) {
        cout << isTriangleNumber(num) << endl;
    }
    else if (test == 2) {
        cout << isPalindrome(num) << endl;
    }
    else if (test == 3) {
        cout << isPowerNumber(num) << endl;
    }
    else if (test == 4) {
        cout << isAbundantNumber(num) << endl;
    }
    return 0;
}
