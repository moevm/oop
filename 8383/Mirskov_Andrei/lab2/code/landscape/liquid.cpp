//
// Created by andrei on 02.03.2020.
//

#include "liquid.h"

char Liquid::getType() {
    return this->type;
}

void Liquid::unitLeft(Unit *unit) {
    unit->setDamage(unit->getDamage() + 1);
}

void Liquid::unitCame(Unit *unit) {
    unit->setDamage(unit->getDamage() - 1);
}
