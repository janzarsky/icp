#ifndef PILE_FACTORY_H
#define PILE_FACTORY_H
#include "Piles.hpp"


class Pile_Factory{
  public:
    Pile_Interface * GetTargetPile(){
      return new TargetPile;
    }
    Pile_Interface * GetHomePile(){
      return new HomePile;
    }
    Pile_Interface * GetStoragePile(){
      return new StoragePile;
    }
    template<typename T> Pile_Interface * GetStoragePile(T vec){
      return new StoragePile(vec);
    }
    template<typename T> Pile_Interface * GetTargetPile(T vec){
      return new TargetPile(vec);
    }
};

#endif
