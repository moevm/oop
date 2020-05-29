//
// Created by andrei on 02.03.2020.
//

#include "weapon.h"


int Weapon::getDamage() {
    return this->damage;
}

char Weapon::getType() {
    return 'w';
}

void Weapon::use(Unit *unit) {
    unit->setDamage(unit->getDamage() + this->getDamage());
}
