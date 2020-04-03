//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_SPEAR_H
#define OOP_LB1__2_SPEAR_H

#include "Weapon.h"

class Spear : public Weapon
{
public:
    Spear(){
        damage = 25;
        type = WeaponType::PHYSIC;
    }
};

#endif //OOP_LB1__2_SPEAR_H
