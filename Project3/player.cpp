#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
class Simple_Player: public Player {
    // REQUIRES: bankroll >= minimum
    // MODIFIES: player
    // EFFECTS: follow the simple player pattern, play the game
    // places the minimum allowable wager
public:
    int bet(unsigned int bankroll, unsigned int minimum) override;
    bool draw(Card dealer, const Hand &player) override;
    void expose(Card c) override;
    void shuffled() override ;
};

class Count_Player: public Simple_Player {
    int count{0};
    // REQUIRES: bankroll >= minimum
    // MODIFIES: player
    // EFFECTS: follow the count player pattern, play the game
    // keeps a running “count” of the cards
public:
    int bet(unsigned int bankroll, unsigned int minimum) override;
    bool draw(Card dealer, const Hand &player) override;
    void expose(Card c) override;
    void shuffled() override;
};


int Simple_Player::bet(unsigned int bankroll, unsigned int minimum) {
    return (int)minimum;
}

bool Simple_Player::draw(Card dealer, const Hand &player) {
    if (!player.handValue().soft) { // the player has a hard count
        if (player.handValue().count <= 11) return true;
        else if (player.handValue().count == 12) {
            return !(dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX);
        }
        else if (player.handValue().count <= 16) {
            return !(TWO <= dealer.spot && dealer.spot <= SIX);
        }
        else return false;
    }
    else { // the player has a soft count
        if (player.handValue().count <= 17) return true;
        else if (player.handValue().count == 18) {
            return !(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot== EIGHT);
        }
        else return false;
    }
}

// the Simple player does nothing for expose and shuffled events.
void Simple_Player::expose(Card c) {}
void Simple_Player::shuffled() {}

int Count_Player::bet(unsigned int bankroll, unsigned int minimum) {
    if (count >= 2 && (bankroll >= 2 * minimum)) return 2 * (int)minimum;
    else return Simple_Player::bet(bankroll, minimum);
}

bool Count_Player::draw(Card dealer, const Hand &player) {return Simple_Player::draw(dealer, player);}

void Count_Player::expose(Card c) {
    if (c.spot >= TEN) count -= 1;
    if (TWO <= c.spot && c.spot <= SIX) count += 1;
}

void Count_Player::shuffled() {count = 0;} // when shuffled, reset count to zero

// static global instance of each of the two Players
static Simple_Player simple_return;
static Count_Player count_return;
// return pointers to each of these two global instances
Player *get_Simple() {
    return &simple_return;
}
Player *get_Counting() {
    return &count_return;
}
