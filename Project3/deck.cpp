#include "deck.h"
Deck::Deck() {
    for (int i = 0; i < 13; i++) {
        deck[i].suit = SPADES;
        deck[i + 13].suit = HEARTS;
        deck[i + 26].suit = CLUBS;
        deck[i + 39].suit = DIAMONDS;
    }
    for (int j = 0; j <= 39; j+=13) {
        deck[j].spot = TWO;
        deck[j + 1].spot = THREE;
        deck[j + 2].spot = FOUR;
        deck[j + 3].spot = FIVE;
        deck[j + 4].spot = SIX;
        deck[j + 5].spot = SEVEN;
        deck[j + 6].spot = EIGHT;
        deck[j + 7].spot = NINE;
        deck[j + 8].spot = TEN;
        deck[j + 9].spot = JACK;
        deck[j + 10].spot = QUEEN;
        deck[j + 11].spot = KING;
        deck[j + 12].spot = ACE;
    }
    next = 0;

}

void Deck::reset() {
    Deck new_deck;
    for (int i = 0; i < DeckSize; i++) {
        deck[i] = new_deck.deck[i];
    }
    next = 0;

}

void Deck::shuffle(int n) {

    //没考虑dealt
    Deck temp;
    int left = 0;
    int num = 0;
    int right = n;
    do {
        if (right < DeckSize) temp.deck[num++] = deck[right++];
        if (left < DeckSize - n) temp.deck[num++] = deck[left++];
    } while (num < DeckSize);
    for (int i = 0; i < DeckSize; i++) {
        deck[i] = temp.deck[i];
    }
    next = 0;



}

Card Deck::deal() {
    return deck[next];
}

int Deck::cardsLeft() {
    return DeckSize - next;
}