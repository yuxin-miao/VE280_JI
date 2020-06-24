#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cassert>
#include "deck.h"
using namespace std;


int main() {
    Deck one;

    one.shuffle(26);
    one.reset();

}