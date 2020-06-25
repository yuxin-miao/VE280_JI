//
// Created by Cheney Ni on 2019/11/27.
//
#include <iostream>
#include "hand.h"
#include "card.h"
using namespace std;

int main() {
    Hand hand;
    cout << hand.handValue().count << " " << hand.handValue().soft << endl;
    hand.addCard({JACK, CLUBS});
    cout << hand.handValue().count << " " << hand.handValue().soft << endl;
    hand.addCard({ACE, CLUBS});
    cout << hand.handValue().count << " " << hand.handValue().soft << endl;
    hand.addCard({ACE, CLUBS});
    cout << hand.handValue().count << " " << hand.handValue().soft << endl;
    // Here count = 12, soft = 0

    hand.addCard({ACE, CLUBS});
    cout << hand.handValue().count << " " << hand.handValue().soft << endl;
    return 0;
}
