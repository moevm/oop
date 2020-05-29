//
// Created by andrei on 02.03.2020.
//

#include "potion.h"

int Potion::getHealth() {
    return this->health;
}

char Potion::getType() {
    return 'p';
}

void Potion::use(Unit *unit) {
    unit->heal(this->getHealth());
}
