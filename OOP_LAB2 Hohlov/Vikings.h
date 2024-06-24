

#ifndef OOP_LAB1_VIKINGS_H
#define OOP_LAB1_VIKINGS_H

#include "Unit.h"
#include "IronArmor.h"
#include "WeaponFlyWeight.h"
#include "ArmorFlyWeight.h"

class Viking: public Unit {

public:

    Viking(Weapon &weapon, int health): Unit(UnitType::VIKINGS, *ArmorFlyWeight::getFlyWeight<IronArmor>(), weapon, health) {}

};

#endif //OOP_LAB1_VIKINGS_H
