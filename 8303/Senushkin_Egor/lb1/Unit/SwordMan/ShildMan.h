//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_SHILDMAN_H
#define OOP_LB1__2_SHILDMAN_H

#include "../../Weapon/Sword.h"
#include "SwordMan.h"

class ShildMan : public SwordMan{
public:
    ShildMan() {
        weapon = Sword();
        health = 200;
    }
    std::string type() const { return "ShildMan"; }
    ~ShildMan() = default;
};

#endif //OOP_LB1__2_SHILDMAN_H
