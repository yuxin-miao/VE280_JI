/*
 * VE280 Lab 3, SU2020.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;

bool canWim_helper(const int arr[], int arr_record[], int position, int count) {
    if (position > count - 1 | position < 0) return false;
    if (arr_record[position] == 1) return false; 
    arr_record[position] = 1; //你的record没用？？
    if (arr[position] == 280) return true;
    return (canWim_helper(arr, arr_record, position+arr[position], count) | canWim_helper(arr, arr_record, position-arr[position], count));
}


bool canWin(int count, int arr[], int position) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    
    // TODO: implement this function
    int arr_record[MAXSIZE] = {0}; // record the status of the cards
    return canWim_helper(arr, arr_record, position, count);
}

int main() {
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position);
}
