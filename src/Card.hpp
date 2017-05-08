/**
 * @file    Card.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief  Declaration of class Card representing one card in game
 */

#ifndef CARD_H
#define CARD_H

#define DEBUG
#ifdef DEBUG
#define DEB(x) do{\
  std::cerr<< x;}\
  while(0)
#endif

#ifndef DEBUG
#define DEB(X)
#endif


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
