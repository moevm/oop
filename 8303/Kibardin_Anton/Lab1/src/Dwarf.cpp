//
// Created by anton on 27.02.2020.
//

#include "Dwarf.h"
Dwarf::Dwarf(){
    health = 250;
    armor = 250;
    attack = 40;
    attackRange = 2;
}
char Dwarf::getClass() const {
    return 'D';
}