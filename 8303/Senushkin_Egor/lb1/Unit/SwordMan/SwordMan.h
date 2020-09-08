//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_SWORDMAN_H
#define OOP_LB1__2_SWORDMAN_H

#include "../Unit.h"
#include "../../Armor/MediumArmor.h"

class SwordMan : public Unit{
public:
    SwordMan() {
        armor = MediumArmor();
    }
    std::string type() const { return "SwordMan"; }
    ~SwordMan() = default;
};

#endif //OOP_LB1__2_SWORDMAN_H
