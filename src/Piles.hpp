/**
 * @file    Piles.hpp
 * @author  Jan Zarsky (xzarsk03@stud.fit.vutbr.cz)
 *          Andrei Paplauski (xpapla00@stud.fit.vutbr.cz)
 * @brief   Implementation of interfaces of differenet game piles
 */


#ifndef PILES_H
#define PILES_H

#include "Pile_interface.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>



using namespace std;

/**
  Class for 7 target piles, implements pile interface
*/
class TargetPile:public Pile_Interface{
  public:

    TargetPile() = delete;

    /**
  		Construct target pile from vector of cards
  		@param vec Vector as base for construction
  	*/
    TargetPile(std::vector<card>& vec)
    {
    	for (card cd : vec)
    	{
    		this->cards.push_back(cd);
    		this->size++;
    	}
    }

    /**
  		Add card to target pile with appropriate controls
  		@param cd Card for adding
  		@param flags Defines behaviour
  		@return Success
  	*/
    int AddCard(card& cd, int flags) final
    {

      if(!(flags & INSERT_ONLY)){
        int Dtemp_suit = (*(cards.end() - 1)).getSuit();
        int Dtemp_value = (*(cards.end() - 1)).getValue();


        if(this->IsEmpty()){
          if(cd.getValue() != K){
            cerr << "ERROR("<<__LINE__<<"):You can place only K to empty field" << endl;
            return -1;
          }
        }
        else if(cd.getValue() + 1 != static_cast<unsigned>(Dtemp_value)) {
          cerr << "ERROR("<<__LINE__<<"):You can't place this card(s) here";
          DEB("s value="<<cd.getValue()<< "  d value: "<<Dtemp_value << endl);
          return -1;
        }

        switch (cd.getSuit()) {
        case DIAMONDS:
        case HEARTS:
          if (Dtemp_suit == DIAMONDS || Dtemp_suit == HEARTS) {
            cerr << "ERROR("<<__LINE__<<"):Can't place on same color" << endl;
            return -1;
          }
          break;
        default:
          if (Dtemp_suit == SPADES || Dtemp_suit == CLUBS) {
            cerr << "ERROR("<<__LINE__<<"):Can't place on same color" << endl;
            return -1;
          }
        }
      }

      this->cards.push_back(cd);
    	this->shownCards++;
    	if (flags & INSERT_ONLY) this->shownCards--;
    	this->size++;
      return 0;
    }

    /**
      Add vector of cards to target pile with appropriate controls
      @param cd_vec Vector of cards for adding
      @param flags Defines behaviour
      @return Success
    */
    int AddCard(std::vector<card> cd_vec, int flags)
    {
    	//std::cout<< "first card:" << (this->shownCards.front()).getSuit() << " " << (this->shownCards.front()).getValue() << "\n";
    	//std::cout << "pushing card:" << cd.getSuit() << " " << cd.getValue() << "\n";
      if(!(flags & INSERT_ONLY)){
        int Dtemp_suit = (*(cards.end() - 1)).getSuit();
        int Dtemp_value = (*(cards.end() - 1)).getValue();
        card  cd = *(cd_vec.begin());

        if(this->IsEmpty()){
          if(cd.getValue() != K){
            cerr << "ERROR("<<__LINE__<<"):You can place only K to empty field" << endl;
            return -1;
          }
        }
        else if(cd.getValue() + 1 != static_cast<unsigned>(Dtemp_value)) {
          cerr << "ERROR("<<__LINE__<<"):You can't place this card(s) here ";
          DEB("s value="<<cd.getValue()<< "  d value: "<<Dtemp_value << endl);
          return -1;
        }

        switch (cd.getSuit()) {
        case DIAMONDS:
        case HEARTS:
          if (Dtemp_suit == DIAMONDS || Dtemp_suit == HEARTS) {
            cerr << "ERROR("<<__LINE__<<"):Can't place on same color" << endl;
            return -1;
          }
          break;
        default:
          if (Dtemp_suit == SPADES || Dtemp_suit == CLUBS) {
            cerr << "ERROR("<<__LINE__<<"):Can't place on same color" << endl;
            return -1;
          }
        }
      }

    	for (auto iter = cd_vec.begin();iter != cd_vec.end();iter++ ) {
    		this->cards.push_back(*iter);
    		this->shownCards++;
    		if (flags & INSERT_ONLY) this->shownCards--;
    		this->size++;
    	}
      return 0;
    }

    ~TargetPile(){}
};


/**
  Class for 4 home piles, implements pile interface
*/
class HomePile:public Pile_Interface{
  public:
    /**
  		Construct empty home pile
  	*/
    HomePile(){
      this->cards = std::vector<card>{};
      this->size = 0;
      shownCards = 0;
    }

    /**
      Construct home pile from vector of cards
      @param vec Vector as base for construction
    */
    HomePile(std::vector<card>& vec)
    {
    	for (card cd : vec)
    	{
    		this->cards.push_back(cd);
    		this->size++;
    	}
    }

    /**
  		Add card to home pile with appropriate controls
  		@param cd Card for adding
  		@param flags Defines behaviour
  		@return Success
  	*/
    int AddCard(card& cd, int flags) final
    {

      if(!(flags & INSERT_ONLY)){
        int Dtemp_suit = (*(cards.end() - 1)).getSuit();
        int Dtemp_value = (*(cards.end() - 1)).getValue();


        if(this->IsEmpty()){
          if(cd.getValue() != A){
            cerr << "You can place only A to empty field" << endl;
            return -1;
          }
        }
        else if(cd.getValue() - 1 != static_cast<unsigned>(Dtemp_value)) {
          cerr << "You can't place this card(s) here";
          DEB("s value="<<cd.getValue()<< "  d value: "<<Dtemp_value << endl);
          return -1;
        }

        if (cd.getSuit() != Dtemp_suit) {
					cerr << "You must place here cards with same suit" << endl;
					return -1;
				}
        shownCards++;
      }

      this->cards.push_back(cd);
    	this->size++;
      return 0;
    }

    /**
      Add vector of cards to home pile with appropriate controls
      @param cd_vec Vector of cards for adding
      @param flags Defines behaviour
      @return Success
    */
    int AddCard(std::vector<card> cd_vec, int flags)
    {
    	//std::cout<< "first card:" << (this->shownCards.front()).getSuit() << " " << (this->shownCards.front()).getValue() << "\n";
    	//std::cout << "pushing card:" << cd.getSuit() << " " << cd.getValue() << "\n";
      if(cd_vec.size() == 1){
        int Dtemp_suit = 0;
        int Dtemp_value = 0;
        card & cd = *(cd_vec.begin());

        if(!(flags & INSERT_ONLY)){
          if(this->IsEmpty()){
            if(cd.getValue() != A){
              cerr << "You can place only A to empty field" << endl;
              return -1;
            }
            shownCards++;
            this->cards.push_back(cd);
          	this->size++;
            return 0;
          }
          else{
            Dtemp_suit = (*(cards.end() - 1)).getSuit();
            Dtemp_value = (*(cards.end() - 1)).getValue();
            if(cd.getValue() - 1 != static_cast<unsigned>(Dtemp_value)) {
              cerr << "You can't place this card(s) here";
              DEB("s value="<<cd.getValue()<< "  d value: "<<Dtemp_value << endl);
              return -1;
            }
          }

          if (cd.getSuit() != Dtemp_suit) {
        		cerr << "You must place here cards with same suit" << endl;
        		return -1;
        	}
        }
        this->cards.push_back(cd);
      	this->size++;
        return 0;
      }
      else{
        cerr<<"You can't place here more then 1 card"<<endl;
        return -1;
      }
    }

    ~HomePile(){}
};


/**
  Class for storage pile, implements pile interface
*/
class StoragePile:public Pile_Interface{
  public:

    /**
  		Add card to storage pile with appropriate controls
  		@param cd Card for adding
  		@param flags Defines behaviour
  		@return Success
  	*/
    int AddCard(card& cd, int flags)
    {

      if(flags & INSERT_ONLY){
        this->cards.push_back(cd);
      	this->size++;
        return 0;
      }
      else{
        cerr<<"You can't add cards to storage pile\n";
        return -1;
      }
    }

    /**
      Add vector of cards to storage pile with appropriate controls
      @param cd_vec Vector of cards for adding
      @param flags Defines behaviour
      @return Success
    */
    int AddCard(std::vector<card> cd_vec, int flags)
    {
      if(flags & INSERT_ONLY){
        for (auto iter = cd_vec.begin();iter != cd_vec.end();iter++ ) {
      		this->cards.push_back(*iter);
      		this->size++;
      	}
        return 0;
      }
      else{
        cerr<<"You can't add cards to storage pile\n";
        return -1;
      }
    }

    StoragePile() = delete;

    /**
  		Construct storage pile from vector of cards
  		@param vec Vector as base for construction
  	*/
    StoragePile(std::vector<card>& vec)
    {
    	for (card cd : vec)
    	{
    		this->cards.push_back(cd);
    		this->size++;
    	}
      // random_shuffle(cards.begin(),cards.end());
    }

    ~StoragePile(){}
};

#endif
