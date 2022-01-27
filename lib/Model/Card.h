#ifndef _CARD_H_
#define _CARD_H_

#include "Value.h"
#include "Color.h"
#include <utility>

class Card {
private:
    Color _color;
    Value _value;
public:
    /**
     * Constructor pf the card
     * @brief Card Constructor of Card
     * @param color color of card
     * @param value value of card
     */
    Card (Color color, Value value);
    /**
     * getter of the color
     * @brief get_color getter of color
     * @return  color card
     */
    [[nodiscard]] Color get_color () const;
    /**
     * getter of the value
     * @brief get_value getter of value
     * @return value of card
     */
    [[nodiscard]] Value get_value () const;
    /**
     *
     * @brief get_value_card getter
     * conversion the type Value on int
     * @return int the value of the card
     */
    [[nodiscard]]  int get_value_card()const;


};

#endif //_CARD_H_
