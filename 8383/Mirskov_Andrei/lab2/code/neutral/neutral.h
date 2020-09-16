//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_NEUTRAL_H
#define OOP_LAB1_NEUTRAL_H

class Unit;

#include "../units/unit.h"

class Neutral {
public:
    virtual char getType() = 0;

    virtual void use(Unit*) = 0;
};


#endif //OOP_LAB1_NEUTRAL_H
