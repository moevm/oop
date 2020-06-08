#ifndef BATTLEFORHONOUR_INFANTRY_H
#define BATTLEFORHONOUR_INFANTRY_H


#include "../../Unit.h"
#include "../../../Armor/Armor.h"
#include "../../../Weapon/WeaponFlyweight.h"
#include "../../../Armor/ArmorFlyweight.h"

class Infantry: public Unit {

public:
    Infantry(Weapon &weapon, int health):
        Unit(UnitType::INFANTRY, *ArmorFlyweight::getFlyweight<PlateMail>(), weapon, health) {}
};


#endif //BATTLEFORHONOUR_INFANTRY_H
