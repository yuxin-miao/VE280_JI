#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cassert>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
using namespace std;


int main(int argc, char *argv[]) {
    int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);
    string type = argv[3];
    for (int num = 0; num < 7; num++) {
        cout << "Shuffling the deck\n";
        int cut = get_cut();
        cout << "cut at " << cut << endl;

    }


}