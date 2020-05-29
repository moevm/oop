//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_POTION_H
#define OOP_LAB1_POTION_H


#include "neutral.h"

class Potion: public Neutral {
public:
    char getType() override;

    void use(Unit*) override;

    int getHealth();

private:
    const int health = 5;
};


#endif //OOP_LAB1_POTION_H
