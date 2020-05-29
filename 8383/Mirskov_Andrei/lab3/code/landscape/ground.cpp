//
// Created by andrei on 02.03.2020.
//

#include "ground.h"

char Ground::getType() {
    return this->type;
}

void Ground::unitLeft(Unit* unit) {
    unit->setArmor(unit->getArmor() + 1);
}

void Ground::unitCame(Unit *unit) {
    unit->setArmor(unit->getArmor() - 1);
}
