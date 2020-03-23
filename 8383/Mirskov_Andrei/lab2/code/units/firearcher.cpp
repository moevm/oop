//
// Created by andrei on 19.02.2020.
//

#include "firearcher.h"

FireArcher::FireArcher(int x, int y) : Archer() {
    this->x = x;
    this->y = y;
    this->damage.setValue(5);
    this->armor.setValue(9);
}

char FireArcher::getType() {
    return 'F';
}
