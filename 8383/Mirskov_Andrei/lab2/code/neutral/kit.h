//
// Created by andrei on 23.03.2020.
//

#ifndef OOP_LAB1_KIT_H
#define OOP_LAB1_KIT_H


#include "mainNeutral.h"

class Kit: public MainNeutral {
public:
    using MainNeutral::MainNeutral;

    char getType() override;

    int getArmor();

    int getDamage();

private:
    const int armor = 3;
    const int damage = 3;
};


#endif //OOP_LAB1_KIT_H
