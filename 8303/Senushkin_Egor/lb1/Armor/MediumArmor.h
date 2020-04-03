//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_MEDIUMARMOR_H
#define OOP_LB1__2_MEDIUMARMOR_H

#include "Armor.h"

class MediumArmor : public Armor{
public:
    MediumArmor(){
        BlockingDamage = 10;
        type = ArmorType::MEDIUM;
    }
};

#endif //OOP_LB1__2_MEDIUMARMOR_H
