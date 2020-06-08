#ifndef BATTLEFORHONOUR_BOW_H
#define BATTLEFORHONOUR_BOW_H


#include "Weapon.h"

class Bow: public Weapon{

public:

    Bow(){
        damage = 10;
        type = WeaponType::DISTANCE;
    }

};


#endif //BATTLEFORHONOUR_BOW_H
