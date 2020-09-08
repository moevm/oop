//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_BOW_H
#define OOP_LB1__2_BOW_H

#include "Weapon.h"

class Bow : public Weapon
{
public:
    Bow(){
        damage = 20;
        type = WeaponType::RANGE;
    }
};

#endif //OOP_LB1__2_BOW_H
