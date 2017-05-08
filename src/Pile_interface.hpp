/**
 * @file    Pile_interface.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Class Pile_Interface which is implements 'interface' for all piles in game
 */


#ifndef PILE_INTERFACE_H
#define PILE_INTERFACE_H
#include "Card.hpp"
#include <vector>
#include <iostream>
#include <string>

namespace solitaire
{

/**
  Implements interface for all piles in game
*/
class Pile_Interface{
  protected:
    std::vector<card> cards;  //!< Vector with all cards of current pile
  public:
    static const int PUT = 0;
    static const int INSERT_ONLY = 1;
    unsigned size = 0;    //!< Size of current pile
    unsigned shownCards = 1;  //!< Amount of shown cards in the pile

    Pile_Interface(){};

    virtual int AddCard(card&,int = PUT) = 0;
    virtual int AddCard(std::vector<card>, int = PUT) = 0 ;

    /**
  		Pop card from pile
  		@return Poped card
  	*/
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
    		throw std::invalid_argument("Pile is empty, can't POP card\n");
    	}
    }

    /**
  		Convert current pile into string for further saving
  		@return Pile converted to string
  	*/
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
      if(cards.empty()) temp+=',';
      return temp;
    }

    /**
  		Getter for pile
  		@return Vector of cards in current pile
  	*/
  	std::vector<card>& GetPile()
  	{
  			return this->cards;
  	}

    /**
      Test if current pile have cards
  		@return Is current pile empty
  	*/
    bool IsEmpty()
  	{
  		return this->size < 1 ? 1 : 0;
  	}

    virtual ~Pile_Interface() = default;

};

}

#endif
