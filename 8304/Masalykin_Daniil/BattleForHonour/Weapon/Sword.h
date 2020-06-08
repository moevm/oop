#ifndef BATTLEFORHONOUR_SWORD_H
#define BATTLEFORHONOUR_SWORD_H


#include "Weapon.h"

class Sword: public Weapon{

public:
    Sword(){

        damage = 10;
        type = WeaponType::PHYSIC;

    }

};


#endif //BATTLEFORHONOUR_SWORD_H
