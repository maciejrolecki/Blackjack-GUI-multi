#include "Card.h"

Card::Card (Color color, Value value) : _color (std::move(color)), _value (value)
{}

 Color Card::get_color () const
{
    return _color;
}

Value Card::get_value () const
{
    return _value;
}

int Card::get_value_card()const{
    return static_cast<int>(_value);
}
