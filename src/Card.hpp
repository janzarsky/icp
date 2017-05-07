#ifndef CARD_H
#define CARD_H

/**
Enum type for card suits
*/
enum cardsuit
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

const unsigned J=11, Q=12, K=13, A=1;

/**
Class representing card
*/
class card
{
	cardsuit suit; //!< Suit of card
	unsigned value;  //!< Value of card
public:
	card(cardsuit,unsigned);
	cardsuit getSuit();
	unsigned getValue();
	~card();
};
#endif
