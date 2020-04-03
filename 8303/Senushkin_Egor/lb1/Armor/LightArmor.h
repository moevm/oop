//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_LIGHTARMOR_H
#define OOP_LB1__2_LIGHTARMOR_H

#include "Armor.h"

class LightArmor : public Armor{
public:
    LightArmor(){
        BlockingDamage = 5;
        type = ArmorType::LIGHT;
    }
};

#endif //OOP_LB1__2_LIGHTARMOR_H
