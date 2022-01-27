#include <algorithm>
#include <random>
#include "Deck.h"


Deck::Deck() {
    initializeDeck();
}


void Deck::initializeDeck(){
    for(size_t i =0 ; i<13;++i)
        for(size_t j =0 ; j<4;++j)
            cardList.push_back(Card(arrays_colors[j],arrays_values[i]));
    shuffle_cards();
}

void Deck::shuffle_cards ()
{
    auto rng = std::default_random_engine {};
    std::shuffle (cardList.begin (), cardList.end (), rng);
}

bool Deck::is_empty ()
{
    return cardList.empty ();
}

const std::vector<Card> Deck::get_card_list()const{
    return cardList;
}

Card Deck::hit ()
{
    if(is_empty()) initializeDeck();
    Card a = Card(cardList.back());
    cardList.pop_back();
    return a;
}
