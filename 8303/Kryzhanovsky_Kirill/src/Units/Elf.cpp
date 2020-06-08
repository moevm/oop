//
// Created by therealyou on 11.02.2020.
//

#include "Elf.h"


Elf::Elf(int speed, int armor, int damage, int health, int rangeAttack) :
Magicians(speed, armor, damage, health, rangeAttack) {

}

char Elf::getCharType() const  {
    return 'E';
}
