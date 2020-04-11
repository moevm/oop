//
// Created by andrei on 23.03.2020.
//

#include "kit.h"

char Kit::getType() {
    return 'k';
}

int Kit::getDamage() {
    return this->damage;
}

int Kit::getArmor() {
    return this->armor;
}

void Kit::use(Unit *unit) {
    unit->setDamage(unit->getDamage() + this->getDamage());
    unit->setArmor(unit->getArmor() + this->getArmor());
}
