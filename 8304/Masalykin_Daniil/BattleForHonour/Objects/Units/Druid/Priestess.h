#ifndef BATTLEFORHONOUR_PRIESTESS_H
#define BATTLEFORHONOUR_PRIESTESS_H


#include "Druid.h"
#include "../../../Weapon/Weapon.h"

class Priestess: public Druid{

public:
    Priestess():
        Druid(*WeaponFlyweight::getFlyWeight<StarFall>(), 20){}
};

#endif //BATTLEFORHONOUR_PRIESTESS_H
