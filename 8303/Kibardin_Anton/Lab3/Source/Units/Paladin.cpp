//
// Created by anton on 27.02.2020.
//

#include "Paladin.h"
#define PALADIN_SPECIFICATION {300, 150, 35, 2}

Paladin::Paladin(): Warrior(PALADIN_SPECIFICATION){}

char Paladin::getClass() const {
    return 'p';
}