//
// Created by anton on 27.02.2020.
//

#include "Necromancer.h"
#define NECROMANCER_SPECIFICATION {100, 25, 10, 5}

Necromancer::Necromancer():Wizard(NECROMANCER_SPECIFICATION){}

Necromancer::Necromancer(Specifications loaded): Wizard(loaded) {}

char Necromancer::getClass() const {
    return 'n';
}