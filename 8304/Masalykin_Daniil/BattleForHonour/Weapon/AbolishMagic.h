#ifndef BATTLEFORHONOUR_ABOLISHMAGIC_H
#define BATTLEFORHONOUR_ABOLISHMAGIC_H


#include "Weapon.h"

class AbolishMagic: public Weapon{

public:

    AbolishMagic(){

        damage = 20;
        type = WeaponType::MAGIC;

    }

};


#endif //BATTLEFORHONOUR_ABOLISHMAGIC_H
