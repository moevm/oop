//
// Created by anton on 27.02.2020.
//

#include "Dwarf.h"
#define DWARF_SPECIFICATIONS {250, 300, 40, 2}

Dwarf::Dwarf():Warrior(DWARF_SPECIFICATIONS){}

char Dwarf::getClass() const {
    return 'd';
}