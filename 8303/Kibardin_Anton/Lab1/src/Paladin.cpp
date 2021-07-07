//
// Created by anton on 27.02.2020.
//

#include "Paladin.h"
Paladin::Paladin(){
    health = 300;
    armor = 150;
    attack = 35;
    attackRange = 2;
}

char Paladin::getClass() const {
    return 'P';
}