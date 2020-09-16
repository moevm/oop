//
// Created by andrei on 23.03.2020.
//

#ifndef OOP_LAB1_KIT_H
#define OOP_LAB1_KIT_H


#include "neutral.h"

class Kit: public Neutral {
public:
    char getType() override;

    void use(Unit*) override;

    int getArmor();

    int getDamage();

private:
    const int armor = 3;
    const int damage = 3;
};


#endif //OOP_LAB1_KIT_H
