//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_PALADIN_H
#define OOP_1_PALADIN_H

#include "Warrior.h"

class Paladin: public Warrior{
public:
    Paladin();

    char getClass() const final;

};


#endif //OOP_1_PALADIN_H
