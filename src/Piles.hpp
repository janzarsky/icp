#ifndef PILES_H
#define PILES_H

#include "Pile_interface.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>

#define DEBUG
#ifdef DEBUG
#define DEB(x) do{\
  std::cerr<< x;}\
  while(0)
#endif

#ifndef DEBUG
#define DEB(X)
#endif


using namespace std;

class TargetPile:public Pile_Interface{
  public:

    TargetPile() = delete;
    TargetPile(std::vector<card>& vec)
    {
    	for (card cd : vec)
    	{
    		this->cards.push_back(cd);
    		this->size++;
    	}
    }

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
        else if(cd.getValue() + 1 != Dtemp_value) {
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

    int AddCard(std::vector<card> cd_vec, int flags)
    {
    	//std::cout<< "first card:" << (this->shownCards.front()).getSuit() << " " << (this->shownCards.front()).getValue() << "\n";
    	//std::cout << "pushing card:" << cd.getSuit() << " " << cd.getValue() << "\n";
      if(!(flags & INSERT_ONLY)){
        int Dtemp_suit = (*(cards.end() - 1)).getSuit();
        int Dtemp_value = (*(cards.end() - 1)).getValue();
        card  cd = *(cd_vec.end()-1);

        if(this->IsEmpty()){
          if(cd.getValue() != K){
            cerr << "ERROR("<<__LINE__<<"):You can place only K to empty field" << endl;
            return -1;
          }
        }
        else if(cd.getValue() + 1 != Dtemp_value) {
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

    	for (auto iter = cd_vec.rbegin();iter != cd_vec.rend();iter++ ) {
    		this->cards.push_back(*iter);
    		this->shownCards++;
    		if (flags & INSERT_ONLY) this->shownCards--;
    		this->size++;
    	}
      return 0;
    }

    ~TargetPile(){}
};

class HomePile:public Pile_Interface{
  public:
    HomePile(){
      this->cards = std::vector<card>{};
      this->size = 0;
    }


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
        else if(cd.getValue() - 1 != Dtemp_value) {
          cerr << "You can't place this card(s) here";
          DEB("s value="<<cd.getValue()<< "  d value: "<<Dtemp_value << endl);
          return -1;
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
            this->cards.push_back(cd);
          	this->size++;
            return 0;
          }
          else{
            Dtemp_suit = (*(cards.end() - 1)).getSuit();
            Dtemp_value = (*(cards.end() - 1)).getValue();
            if(cd.getValue() - 1 != Dtemp_value) {
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

class StoragePile:public Pile_Interface{
  public:
    int AddCard(card& cd, int flags)
    {
      cerr<<"You can't add cards to storage pile\n";
      return -1;
    }
    int AddCard(std::vector<card> cd_vec, int flags)
    {
      cerr<<"You can't add cards to storage pile\n";
      return -1;
    }
    StoragePile() = delete;
    StoragePile(std::vector<card>& vec)
    {
    	for (card cd : vec)
    	{
    		this->cards.push_back(cd);
    		this->size++;
    	}
    }

    ~StoragePile(){}
};

#endif
