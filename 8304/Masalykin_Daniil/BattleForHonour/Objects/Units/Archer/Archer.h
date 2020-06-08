#ifndef BATTLEFORHONOUR_ARCHER_H
#define BATTLEFORHONOUR_ARCHER_H


#include "../../../Weapon/Weapon.h"
#include "../../Unit.h"
#include "../../../Weapon/WeaponFlyweight.h"
#include "../../../Armor/ArmorFlyweight.h"

class Archer: public Unit{

public:
    Archer(Armor &armor, int health):
        Unit(UnitType::ARCHER, armor, *WeaponFlyweight::getFlyWeight<Bow>(), health){}
};


#endif //BATTLEFORHONOUR_ARCHER_H
