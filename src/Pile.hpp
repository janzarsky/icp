#ifndef PILE_H
#define PILE_H
#include "Card.hpp"
#include <vector>
#include <stdlib.h>
#include <iostream>

#define PUT 0
#define INSERT_ONLY 1

class pile
{

	std::vector<card> cards;


public:
	unsigned size = 0;
	unsigned shownCards = 1;
	void AddCard(card&,int = PUT);
	void AddCard(std::vector<card>, int = PUT);
	card& PopCard();

	//return pile of cards
	std::vector<card>GetPile()
	{
		if (!this->IsEmpty())
		{
			return this->cards;
		}
		else
		{
			/*std::cerr << "Error: pile is empty, can't return the pile\n";
			exit(-1);*/
			return std::vector<card>{};
		}
	}

	//check if pile is empty
	bool IsEmpty()
	{
		return this->size < 1 ? 1 : 0;
	}
	pile(std::vector<card>&);
	pile();
	~pile();
};
#endif
