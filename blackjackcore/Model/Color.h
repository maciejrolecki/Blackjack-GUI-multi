#ifndef _COLOR_H_
#define _COLOR_H_

#include "iostream"

/**
 * @brief The Color enum
 * with the different type of card
 */
enum Color {
    CLUB=0, DIAMOND=1, HEART=2, SPADE=3
};

using color = std::pair<Color, const char*>;
struct colors {
public:
    /**
     * pair of color
     *
    */

    constexpr static const color CLUBS{CLUB, "Trèfle"};
    constexpr static const color DIAMONDS{DIAMOND, "Carreau"};
    constexpr static const color HEARTS{HEART, "Coeur"};
    constexpr static const color SPADES{SPADE, "Pique"};
};

#endif //_COLOR_H_
