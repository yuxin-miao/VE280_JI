/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>
#include <list>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() {
    // TODO: implement Eratosthenes Sieve Algorithm
    fill_n(isPrime, RANGE + 1, 1);
    for (int i = 0; i < 2; i++) {
        isPrime[i] = false;
    }
    for (int i = 2; i < RANGE + 1; i++) {
        if (isPrime[i]) {
            /*for (int j = i * 2; j < RANGE + 1; j++) {
                if (j % i == 0) {
                    isPrime[j] = false;
                }
            }*/
            // IF use the above loop, the time would be the same as judge one by one
            for (int j = 2; i * j < RANGE + 1; j++)
                isPrime[i*j] = false;
        }
    }

}

int main() {
    // TODO: generate lookup table
    generateIsPrime();

    // TODO: read input and check if each num is prime
    int x;
    cin >> x;
    int num[30] = {0};
    for (int i = 0; i < x; i++){
        cin >> num[i];
    }
    for (int i = 0; i < x; i++) {
        if (isPrime[num[i]]) cout << num[i] << " ";
    }
    cout << endl;
    return 0;
}
