//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_HEAVYARMOR_H
#define OOP_LB1__2_HEAVYARMOR_H

#include "Armor.h"

class HeavyArmor : public Armor{
public:
    HeavyArmor(){
        BlockingDamage = 15;
        type = ArmorType::HEAVY;
    }
};

#endif //OOP_LB1__2_HEAVYARMOR_H
