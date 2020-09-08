//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_WIZARD_H
#define OOP_LB1__2_WIZARD_H

#include "../../Weapon/MagicStick.h"
#include "Archer.h"

class Wizard : public Archer {
public:
    Wizard(){
        weapon = MagicStick();
        health = 50;
    }

    std::string type() const { return "Wizard"; }
    ~Wizard() = default;
};

#endif //OOP_LB1__2_WIZARD_H
