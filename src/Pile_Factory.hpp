#ifndef PILE_FACTORY_H
#define PILE_FACTORY_H
#include "Piles.hpp"

/**
  Factory for creation of different instanses of piles
*/
class Pile_Factory{
  private:
    vector<Pile_Interface *> piles_pointers; //!< Vector with pointers to all created piles for further deletion
  public:

    /**
  		Construct home pile
  		@return pointer to created pile structure
  	*/
    Pile_Interface * GetHomePile()
    {
      piles_pointers.push_back(new HomePile);
      return piles_pointers.back();
    }

    /**
  		Construct home pile from vector
      @param vec Vector as base for construction
  		@return Pointer to created pile structure
  	*/
    template<typename T> Pile_Interface * GetHomePile(T vec)
    {
      piles_pointers.push_back(new HomePile(vec));
      return piles_pointers.back();
    }

    /**
  		Construct storage pile from vector
      @param vec Vector as base for construction
  		@return Pointer to created pile structure
  	*/
    template<typename T> Pile_Interface * GetStoragePile(T vec)
    {
      piles_pointers.push_back(new StoragePile(vec));
      return piles_pointers.back();
    }

    /**
  		Construct target pile from vector
      @param vec Vector as base for construction
  		@return Pointer to created pile structure
  	*/
    template<typename T> Pile_Interface * GetTargetPile(T vec)
    {
      piles_pointers.push_back( new TargetPile(vec));
      return piles_pointers.back();
    }

    /**
  		Destructor for factory, frees all allocated memory
  	*/
    ~Pile_Factory()
    {
      for(auto pl : piles_pointers){
        delete pl;
      }
      // DEB("INFO: All piles are deleted.\n");
    }
};

#endif
