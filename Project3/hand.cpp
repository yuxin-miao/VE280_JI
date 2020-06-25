#include "hand.h"

Hand::Hand() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::addCard(Card c) {
    int value_add = 0; // the value of card to be added
    if (c.spot <= 8) value_add = c.spot + 2;
    else if (c.spot < 12) value_add = 10;
    else value_add = 11;

    if (!curValue.soft) { // no ACE(11) in previous cards
        if (c.spot == ACE) { // card is ACE
            if (curValue.count <= 10) { // treat ACE as 11
                curValue.count += 11;
                curValue.soft = true;
            }
            else { // treat as 1
                curValue.count += 1;
            }
        }
        else { // card is not ACE
            curValue.count += value_add;
        }
    }

    else if (curValue.soft) { // if already has an ACE and treated as 11
        if (curValue.count + value_add > 21) { // when larger, change the previous ACE to 1
            curValue.count = curValue.count - 10 + value_add;
            curValue.soft = false;
            if (value_add == 11) { // the value added is ACE, determine add it as 11 or 1
                if (curValue.count > 21) {curValue.count -= 10; curValue.soft = false;}
                else curValue.soft = true;
            }
        }
        else curValue.count += value_add;
    }
}

HandValue Hand::handValue() const {
    return curValue;
}