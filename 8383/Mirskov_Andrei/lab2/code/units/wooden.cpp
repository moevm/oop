//
// Created by andrei on 19.02.2020.
//

#include "wooden.h"

WoodenArcher::WoodenArcher(int x, int y) : Archer() {
    this->x = x;
    this->y = y;
    this->damage.setValue(1);
    this->armor.setValue(2);
}

char WoodenArcher::getType() {
    return 'W';
}
