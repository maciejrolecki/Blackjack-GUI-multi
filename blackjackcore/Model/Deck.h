#ifndef _DECK_H_
#define _DECK_H_

#include <array>
#include <vector>
#include "Card.h"
#include "Value.h"

class Deck {
private:
    /**
     * List of card
     * @brief cardList
     */
    std::vector<Card> cardList;

    std::array<Value,13> arrays_values = {ACE,TWO,
                                                THREE,FOUR,FIVE,
                                                SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};

    std::array<Color,4> arrays_colors = {CLUB,DIAMOND,HEART,SPADE};

    /**
     * @brief Initialize deck  with cards.
     *
     * @param myList list of card
     */
    void initializeDeck();

    /**
     * @brief Shuffles the cards in the deck
     */
    void shuffle_cards();

public:
    /**
     * @brief Constructor for a deck object.
     * Fills the deck with 52 cards in a random order.
     */
    Deck();

    /**
     * @brief Verifies if there are no more cards in the deck.
     * @return true if deck is empty
     */
    bool is_empty ();

    /**
     * @brief Returns a copy of the cards that are in the deck
     * @return std::vector<Card> a copy of the deck
     */
    const std::vector<Card> get_card_list() const;

    /**
     * @brief Picks a card from the deck, removes it from the deck and returns it.
     * @return A reference to the card that wad removed from the deck.
     */
    Card hit();
};

#endif //_DECK_H_
