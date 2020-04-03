//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_ARCHER_H
#define OOP_LB1__2_ARCHER_H

#include "../Unit.h"
#include "../../Weapon/Bow.h"

class Archer : public Unit{
public:
    Archer(){
        weapon = Bow();
        health = 80;
    }
    std::string type() const { return "Archer"; }
    ~Archer() = default;
};

#endif //OOP_LB1__2_ARCHER_H
