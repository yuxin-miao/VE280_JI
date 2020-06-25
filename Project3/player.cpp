#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
class Simple_Player: public Player {
public:
    int bet(unsigned int bankroll, unsigned int minimum) override;
    bool draw(Card dealer, const Hand &player) override;
    void expose(Card c) override;
    void shuffled() override ;
};



class Count_Player: public Player {
    int count{0};
public: //不需要constructor？
    int bet(unsigned int bankroll, unsigned int minimum) override;
    bool draw(Card dealer, const Hand &player) override;
    void expose(Card c) override;
    void shuffled() override;
};



int Simple_Player::bet(unsigned int bankroll, unsigned int minimum) {
    return (int)minimum;
}

bool Simple_Player::draw(Card dealer, const Hand &player) {
    int dealer_card_value = 0;
    if (dealer.spot <= 8) dealer_card_value = dealer.spot + 2;
    else if (dealer.spot < 12) dealer_card_value = 10;
    else dealer_card_value = 11;

    if (!player.handValue().soft) { // the player has a hard count
        if (player.handValue().count <= 11) return true;
        else if (player.handValue().count == 12) {
            return !(dealer_card_value == 4 || dealer_card_value == 5 || dealer_card_value == 6);
        }
        else if (13 <= player.handValue().count || player.handValue().count <= 16) {
            return !(2 <= dealer_card_value && dealer_card_value <= 6);
        }
        else return false;
    }
    else { // the player has a soft count
        if (player.handValue().count <= 17) return true;
        else if (player.handValue().count == 18) {
            return !(dealer_card_value == 2 || dealer_card_value == 7 || dealer_card_value == 8);
        }
        else return false;
    }
}

// 'simple' will not use this two methods
void Simple_Player::expose(Card c) {}
void Simple_Player::shuffled() {}

int Count_Player::bet(unsigned int bankroll, unsigned int minimum) {
    if (count >= 2 && (bankroll >= 2 * minimum)) return 2 * (int)minimum;
    else return Player::bet(bankroll, minimum); // 是吗
}

bool Count_Player::draw(Card dealer, const Hand &player) {return Player::draw(dealer, player);} //？？困惑

void Count_Player::expose(Card c) {
    int card_value = 0;
    if (c.spot <= 8) card_value = c.spot + 2;
    else if (c.spot < 12) card_value = 10;
    else card_value = 11;

    if (card_value >= 10) count -= 1;
    if (2 <= card_value && card_value <= 6) count += 1;
}

void Count_Player::shuffled() {count = 0;}


static Simple_Player simple_return;
static Count_Player count_return;

extern Player *get_Simple() {
    return &simple_return;

}

extern Player *get_Counting() {
    return &count_return;
}
