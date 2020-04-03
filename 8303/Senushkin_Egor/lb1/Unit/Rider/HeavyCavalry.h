//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_HEAVYCAVALRY_H
#define OOP_LB1__2_HEAVYCAVALRY_H

#include "Rider.h"
#include "../../Weapon/Sword.h"

class HeavyCavalry : public Rider {
public:
    HeavyCavalry(){
        weapon = Sword();
        health = 400;
    }

    std::string type() const { return "HeavyCavalry"; }
    ~HeavyCavalry() = default;
};

#endif //OOP_LB1__2_HEAVYCAVALRY_H
