#include <iostream>
#include "Card.hpp"

namespace solitaire
{
    card::card(cardsuit cs,unsigned value):suit(cs),value(value)
    {
        if (value < 1 || value > K) {
            std::cerr << "Wrong card inicialization: value" << std::endl;
            exit(-1);
        }
        if (cs < CLUBS || cs > SPADES) {
            std::cerr << "Wrong card inicialization: cardsuit" << std::endl;
            exit(-1);
        }
    }

    cardsuit card::getSuit() {
        return this->suit;
    }

    unsigned card::getValue() {
        return this->value;
    }

    card::~card()
    {
    }
}
