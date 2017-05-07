#ifndef PILE_FACTORY_H
#define PILE_FACTORY_H
#include "Piles.hpp"


class Pile_Factory{
  private:
    vector<Pile_Interface *> piles_pointers;
  public:
    Pile_Interface * GetHomePile()
    {
      piles_pointers.push_back(new HomePile);
      return piles_pointers.back();
    }

    template<typename T> Pile_Interface * GetHomePile(T vec)
    {
      piles_pointers.push_back(new HomePile(vec));
      return piles_pointers.back();
    }


    template<typename T> Pile_Interface * GetStoragePile(T vec)
    {
      piles_pointers.push_back(new StoragePile(vec));
      return piles_pointers.back();
    }

    template<typename T> Pile_Interface * GetTargetPile(T vec)
    {
      piles_pointers.push_back( new TargetPile(vec));
      return piles_pointers.back();
    }


    ~Pile_Factory()
    {
      for(auto pl : piles_pointers){
        delete pl;
      }
      DEB("INFO: All piles are deleted.\n");
    }
};

#endif
