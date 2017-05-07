#ifndef PILE_INTERFACE_H
#define PILE_INTERFACE_H
#include "Card.hpp"
#include <vector>
#include <iostream>
#include <string>


class Pile_Interface{
  protected:
    std::vector<card> cards;
  public:
    static const int PUT = 0;
    static const int INSERT_ONLY = 1;
    unsigned size = 0;
    unsigned shownCards = 1;

    Pile_Interface(){};
    virtual int AddCard(card&,int = PUT) = 0;
    virtual int AddCard(std::vector<card>, int = PUT) = 0 ;
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


    std::string str(){
      using std::to_string;
      std::string temp {""};
      temp += to_string(shownCards);
      for(auto card : cards){
        temp +=',';
        switch(card.getSuit()){
          case CLUBS:
            temp+='C';
            break;
        	case DIAMONDS:
            temp+='D';
            break;
        	case HEARTS:
            temp+='H';
            break;
        	case SPADES:
            temp+='S';
            break;
        }
        temp+= to_string(card.getValue());
      }
      return temp;
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

    virtual ~Pile_Interface() = default;

};

#endif
