#include "Croupier.h"
#include "Deck.h"
#include "Player.h"

void Croupier:: pick(Deck& deck) {
    while (get_score() <=MAX_SCORE) add_card(deck.hit());
}

bool Croupier::strike(){
    return Player::strike();
}
