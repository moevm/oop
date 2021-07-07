//
// Created by anton on 27.02.2020.
//

#include "Elf.h"
Elf::Elf()  {
    health = 125;
    armor = 50;
    attack = 30;
    attackRange = 2;
}
char Elf::getClass() const {
    return 'E';
}