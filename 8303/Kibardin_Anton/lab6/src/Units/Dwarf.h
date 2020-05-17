//
// Created by anton on 27.02.2020.
//

#ifndef OOP_1_DWARF_H
#define OOP_1_DWARF_H

#include "Warrior.h"

class Dwarf: public Warrior{
public:
    Dwarf();
    Dwarf(Specifications);
    char getClass() const final;
};


#endif //OOP_1_DWARF_H
