//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_LONGSWORD_H
#define OOP_LB1__2_LONGSWORD_H

#include "Weapon.h"

class LongSword : public Weapon
{
public:
    LongSword(){
        damage = 20;
        type = WeaponType::PHYSIC;
    }
};

#endif //OOP_LB1__2_LONGSWORD_H
