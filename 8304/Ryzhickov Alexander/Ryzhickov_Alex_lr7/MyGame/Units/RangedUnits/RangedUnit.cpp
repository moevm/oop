//
// Created by Alex on 21.03.2020.
//

#include "RangedUnit.h"
namespace GameUnit {
    RangedUnit::RangedUnit(int startX, int startY, Weapon *unitWeapon, Armor *unitArmor) : Unit(startX, startY,
                                                                                                unitWeapon, unitArmor) {
    }

    RangedUnit::RangedUnit() {

    }
}