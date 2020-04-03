//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_SWORD_H
#define OOP_LB1__2_SWORD_H

#include "Weapon.h"

class Sword : public Weapon
{
public:
    Sword(){
        damage = 10;
        type = WeaponType::PHYSIC;
    }
};

#endif //OOP_LB1__2_SWORD_H
