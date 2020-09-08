//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_MAGICSTICK_H
#define OOP_LB1__2_MAGICSTICK_H

#include "Weapon.h"

class MagicStick : public Weapon
{
public:
    MagicStick(){
        damage = 35;
        type = WeaponType::MAGIC;
    }
};

#endif //OOP_LB1__2_MAGICSTICK_H
