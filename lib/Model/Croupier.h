#ifndef _CROUPIER_H_
#define _CROUPIER_H_

#include "Player.h"
#include "Deck.h"

class Croupier : public Player {
private:
    size_t MAX_SCORE = 17;

public:
    /**
     * @brief Default constructor for a Croupier object. Initializes the Player heritage that he had.
     */
    Croupier()=default;

    /**
     * @brief Hits cards for the croupier until score is higher than 17.
     * @param deck Where to pick the card from.
     */
    void pick(Deck& deck);

    /**
     * @brief Verifies if the croupier did a blackjack in 2 cards.
     * @return true if it is the case, false otherwise.
     */
    bool strike();
};

#endif //_CROUPIER_H_
