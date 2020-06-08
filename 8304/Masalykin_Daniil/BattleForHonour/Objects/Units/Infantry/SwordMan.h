#ifndef BATTLEFORHONOUR_SWORDMAN_H
#define BATTLEFORHONOUR_SWORDMAN_H


#include "Infantry.h"
#include "../../../Weapon/Weapon.h"

class SwordMan: public Infantry{

public:
    SwordMan():
        Infantry(*WeaponFlyweight::getFlyWeight<Sword>(), 100){}
};


#endif //BATTLEFORHONOUR_SWORDMAN_H
