#ifndef BATTLEFORHONOUR_STARFALL_H
#define BATTLEFORHONOUR_STARFALL_H


#include <climits>
#include "Weapon.h"

class StarFall: public Weapon{

public:

    StarFall(){

        damage = 50;
        type = WeaponType::MAGIC;

    }

};

#endif //BATTLEFORHONOUR_STARFALL_H
