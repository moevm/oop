//
// Created by andrei on 02.03.2020.
//

#include "clothes.h"

void Clothes::use(Unit *unit) {
    unit->setArmor(unit->getArmor() + this->getArmor());
}

int Clothes::getArmor() {
    return this->armor;
}

char Clothes::getType() {
    return 'c';
}
