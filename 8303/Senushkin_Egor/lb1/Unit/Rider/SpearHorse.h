//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_SPEARHORSE_H
#define OOP_LB1__2_SPEARHORSE_H

#include "Rider.h"
#include "../../Weapon/Spear.h"

class SpearHorse : public Rider {
public:
    SpearHorse() {
        weapon = Spear();
        health = 300;
    }
    std::string type() const { return "SpearHorse"; }
    ~SpearHorse() = default;
};

#endif //OOP_LB1__2_SPEARHORSE_H
