//
// Created by andrei on 19.02.2020.
//

#include "swordman.h"

SwordMan::SwordMan(int x, int y) : Infantry() {
    this->x = x;
    this->y = y;
    this->damage.setValue(5);
    this->armor.setValue(3);
}

char SwordMan::getType() {
    return 'S';
}
