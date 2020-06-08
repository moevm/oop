#ifndef BATTLEFORHONOUR_SPEAR_H
#define BATTLEFORHONOUR_SPEAR_H


#include "Weapon.h"

class Spear: public Weapon{

public:

    Spear(){

        damage = 20;
        type = WeaponType::PHYSIC;

    }

};


#endif //BATTLEFORHONOUR_SPEAR_H
