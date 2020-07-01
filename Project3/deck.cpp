#include "deck.h"
Deck::Deck() {
    reset();
    next = 0;
}

void Deck::reset() {
    for (int i = 0; i < DIAMONDS + 1; ++i) {
        for (int j = 0; j < ACE + 1; ++j) {
            deck[i * (ACE + 1) + j].spot = Spot(j);
            deck[i * (ACE + 1) + j].suit = Suit(i);
        }
    }
    next = 0;

}

void Deck::shuffle(int n) {
    Deck temp;
    for (int i = 0; i < DeckSize; i++) {
        temp.deck[i] = deck[i];
    }
    int left = 0;
    int num = 0;
    int right = n;
    do {
        if (right < DeckSize) temp.deck[num++] = deck[right++];
        if (left < n) temp.deck[num++] = deck[left++];
    } while (num < DeckSize);
    for (int i = 0; i < DeckSize; i++) {
        deck[i] = temp.deck[i];
    }
    next = 0;
}

Card Deck::deal() {
    DeckEmpty empty;
    if (cardsLeft() == 0) throw empty;
    return deck[next++];
}

int Deck::cardsLeft() {
    return DeckSize - next;
}