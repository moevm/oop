//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_CLOTHES_H
#define OOP_LAB1_CLOTHES_H


#include "neutral.h"
#include "mainNeutral.h"

class Clothes: public MainNeutral {
public:
    using MainNeutral::MainNeutral;

    char getType() override;

    int getArmor();

private:
    const int armor = 5;
};


#endif //OOP_LAB1_CLOTHES_H
