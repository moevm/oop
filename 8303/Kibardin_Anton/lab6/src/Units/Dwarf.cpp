//
// Created by anton on 27.02.2020.
//

#include "Dwarf.h"
#define DWARF_SPECIFICATIONS {250, 300, 40, 2}

Dwarf::Dwarf():Warrior(DWARF_SPECIFICATIONS){}

Dwarf::Dwarf(Specifications loaded):Warrior(loaded) {}

char Dwarf::getClass() const {
    return 'd';
}