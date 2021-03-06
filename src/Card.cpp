/**
 * @file    Card.cpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief  Implementation of class Card
 */

#include "Card.hpp"
#include <iostream>

namespace solitaire
{

/**
	Construct card
	@param cs Card suit
	@param value Value of card
*/
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

/**
	Getter for suit of card
	@return Card's suit
*/
cardsuit card::getSuit() {
	return this->suit;
}

/**
	Getter for value of card
	@return Card's value
*/
unsigned card::getValue() {
	return this->value;
}

card::~card()
{
}

}
