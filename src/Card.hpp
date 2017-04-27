#pragma once

namespace solitaire
{
    enum cardsuit
    {
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES
    };

    const unsigned J=11, Q=12, K=13, A=1;

    class card
    {
        cardsuit suit;
        unsigned value;

    public:
        card(cardsuit,unsigned);
        cardsuit getSuit();
        unsigned getValue();
        ~card();
    };
}
