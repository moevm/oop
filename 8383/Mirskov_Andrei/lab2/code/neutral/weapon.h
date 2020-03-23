//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_WEAPON_H
#define OOP_LAB1_WEAPON_H


#include "neutral.h"
#include "mainNeutral.h"

class Weapon: public MainNeutral {
public:
    using MainNeutral::MainNeutral;

    char getType() override;

    int getDamage();

private:
    const int damage = 5;
};


#endif //OOP_LAB1_WEAPON_H
