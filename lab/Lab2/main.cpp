#include <iostream>
using namespace std;
#define RANGE 100000

bool isPrime[RANGE + 1];
bool isPrime_check[RANGE + 1] = {false};

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
            for (int j = i * 2; j < RANGE + 1; j++) {
                if (j % i == 0) {
                    isPrime[j] = false;
                }
            }
        }
        else continue;
    }
}

// MODIFIES: isPrime_check[]
// EFFECTS: fill in isPrime_check[], true for prime, false otherwise
// traditional method, to compare with the new method
void generateIsPrime_check() {
    fill_n(isPrime_check, RANGE + 1, 1);
    for (int i = 0; i < 2; i++) {
        isPrime_check[i] = false;
    }
    for (int i = 3; i < RANGE + 1; i++) {
        for (int j = 2; j < i; j++) {
            if (i % j == 0) isPrime_check[i] = false;
        }
    }
}

int main() {
    generateIsPrime();
    generateIsPrime_check();
    for (int i = 0; i < RANGE + 1; i++) {
        if (isPrime[i] != isPrime_check[i])
            cout << "WRONG: " << i << " CHECK:" << isPrime_check[i] << " ORIGIN:" << isPrime[i] << endl;
    }

    return 0;
}
