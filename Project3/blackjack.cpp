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

void shuffling (Deck& deck, Player* player);
// MODIFIES: deck, player
// EFFECTS: choose seven cuts then implement the shuffling, tell the player
void deal_cards (Deck &deck, Player* player, Hand& dealer_hand, Hand& player_hand, Card cards[], int& bankroll, int& wager);
// MODIFIES: deck, player, dealer_hand, player_hand, cards
// EFFECTS: perform the four cards deal in one turn
void dealer_turn (Deck &deck, Player* player, Hand& dealer_hand, Hand& player_hand, Card cards[], int& bankroll, int& wager);
// MODIFIES: deck, player, dealer_hand, player_hand, cards
// EFFECTS: for dealer, hit until >= 17. determine the winner.

int main(int argc, char *argv[]) {
    // read in the input
    int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);
    string type(argv[3]);
    // declare 'Deck', 'simple' or 'counting' player and initialize them
    Deck deck;
    Player* player;
    Hand player_hand, dealer_hand;

    if (type == "simple") player = get_Simple();
    else if (type == "counting") player = get_Counting();
    else {cout << "WRONG!" << endl; player = get_Simple();}

    shuffling(deck, player); // shuffles the deck, tell the player

    unsigned int minimum = 5;
    unsigned int thishand = 0;
    do {
        if (bankroll < minimum || hands == 0) break; // thishand = 0; terminate (for the first time)
        // for each hand, initialize
        Card cards[5];
        thishand++;
        player_hand.discardAll();
        dealer_hand.discardAll();

        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if (deck.cardsLeft() < 20) shuffling(deck, player); // fewer than 20 cards left

        int wager = player->bet(bankroll, minimum);
        cout << "Player bets " << wager << endl;
        deal_cards(deck, player, dealer_hand, player_hand, cards, bankroll, wager);

        if (player_hand.handValue().count == 21) { //natural 21
            bankroll += wager * 3 / 2;
            cout << "Player dealt natural 21\n";
        }

        else { // no natural 21
            dealer_turn(deck, player, dealer_hand, player_hand, cards, bankroll, wager);
        }
    } while (hands - thishand > 0 && bankroll >= minimum);
    cout << "Player has " << bankroll << " after " << thishand << " hands\n";
    return 0;
}

void shuffling(Deck& deck, Player* player) {
    cout << "Shuffling the deck\n";
    for (int num = 0; num < 7; num++) {
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        deck.shuffle(cut);
    }

    player->shuffled();
}



void deal_cards (Deck& deck, Player* player, Hand& dealer_hand, Hand& player_hand, Card cards[], int& bankroll, int& wager) {
    for (int i = 0; i < 4; i++) {
        cards[i]  = deck.deal();
    }

    player_hand.addCard(cards[0]);
    player->expose(cards[0]);
    cout << "Player dealt " << SpotNames[cards[0].spot] << " of " << SuitNames[cards[0].suit] << endl;

    dealer_hand.addCard(cards[1]);
    player->expose(cards[1]);
    cout << "Dealer dealt " << SpotNames[cards[1].spot] << " of " << SuitNames[cards[1].suit] << endl;

    player_hand.addCard(cards[2]);
    player->expose(cards[2]);
    cout << "Player dealt " << SpotNames[cards[2].spot] << " of " << SuitNames[cards[2].suit] << endl;

    dealer_hand.addCard(cards[3]); // the hole card, no announce/expose

}

void dealer_turn (Deck &deck, Player* player, Hand& dealer_hand, Hand& player_hand, Card cards[], int& bankroll, int& wager) {
    while (player->draw(cards[1], player_hand)) { // let player draw until stand
        cards[4] = deck.deal();
        cout << "Player dealt " << SpotNames[cards[4].spot] << " of " << SuitNames[cards[4].suit] << endl;
        player->expose(cards[4]);
        player_hand.addCard(cards[4]);
    }
    cout << "Player's total is " << player_hand.handValue().count << endl;
    if (player_hand.handValue().count > 21) { // if player bust
        cout << "Player busts\n";
        bankroll -= wager;
    }
    else { // no player bust, dealer's turn
        cout << "Dealer's hole card is " << SpotNames[cards[3].spot] << " of " << SuitNames[cards[3].suit] << endl;
        player->expose(cards[3]);
        while (dealer_hand.handValue().count < 17) { // deal until reach 17
            cards[4] = deck.deal();
            dealer_hand.addCard(cards[4]);
            player->expose(cards[4]);
            cout << "Dealer dealt " << SpotNames[cards[4].spot] << " of " << SuitNames[cards[4].suit] << endl;
        }
        cout << "Dealer's total is " << dealer_hand.handValue().count << endl;
        if (dealer_hand.handValue().count > 21) { // dealer bust
            cout << "Dealer busts\n";
            bankroll += wager;
        }
        else { // dealer and player both not bust
            if (dealer_hand.handValue().count > player_hand.handValue().count) { // dealer win
                cout << "Dealer wins\n";
                bankroll -= wager;
            }
            else if (dealer_hand.handValue().count < player_hand.handValue().count){ // player win
                cout << "Player wins\n";
                bankroll += wager;
            }
            else  cout << "Push\n"; // equal one, no winner
        }
    }
}