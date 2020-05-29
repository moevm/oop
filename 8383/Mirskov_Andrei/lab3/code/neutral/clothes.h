//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_CLOTHES_H
#define OOP_LAB1_CLOTHES_H


#include "neutral.h"

class Clothes: public Neutral {
public:
    char getType() override;

    void use(Unit* unit) override;

    int getArmor();

private:
    const int armor = 5;
};


#endif //OOP_LAB1_CLOTHES_H
