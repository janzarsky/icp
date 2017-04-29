#ifndef PILE_INTERFACE_H
#define PILE_INTERFACE_H
#include "Card.hpp"
#include <vector>
#include <iostream>


class Pile_Interface{
  protected:
    std::vector<card> cards;
  public:
    static const int PUT = 0;
    static const int INSERT_ONLY = 1;
    unsigned size = 0;
    unsigned shownCards = 1;
    virtual int AddCard(card&,int = PUT);
    virtual int AddCard(std::vector<card>, int = PUT);
    card& PopCard()
    {
    	if (!this->IsEmpty())
    	{
    		card& temp = this->cards.back();
    		this->cards.pop_back();
    		this->size--;
    		if (this->shownCards > 1 || this->size == 0)
    		{
    			this->shownCards--;
    		}
    		return temp;
    	}
    	else
    	{
    		std::cerr << "Error: pile is empty, can't POP card\n";
    		exit(-1);
    	}
    }


    //return pile of cards
  	std::vector<card>& GetPile()
  	{
  			return this->cards;
  	}

    bool IsEmpty()
  	{
  		return this->size < 1 ? 1 : 0;
  	}

    virtual ~Pile_Interface();

};

#endif
