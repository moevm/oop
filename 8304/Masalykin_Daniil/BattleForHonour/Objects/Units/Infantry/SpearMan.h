#ifndef BATTLEFORHONOUR_SPEARMAN_H
#define BATTLEFORHONOUR_SPEARMAN_H


#include "Infantry.h"
#include "../../../Weapon/Weapon.h"

class SpearMan: public Infantry{

public:
    SpearMan():
        Infantry(*WeaponFlyweight::getFlyWeight<Spear>(), 50){}
};


#endif //BATTLEFORHONOUR_SPEARMAN_H
