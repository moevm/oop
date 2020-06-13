//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_WARRIOR_H
#define OOP_1_WARRIOR_H

#include "Unit.h"

class Warrior: public Unit {
public:
    friend class Dwarf;
    friend class Paladin;
};


#endif //OOP_1_WARRIOR_H
