//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_LANDSCAPE_H
#define OOP_LAB1_LANDSCAPE_H

#include "../units/unit.h"

class Landscape {
public:
    virtual char getType() = 0;

    virtual void unitLeft(Unit*) = 0;

    virtual void unitCame(Unit*) = 0;
};


#endif //OOP_LAB1_LANDSCAPE_H
