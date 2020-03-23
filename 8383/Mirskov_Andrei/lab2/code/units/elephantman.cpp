//
// Created by andrei on 19.02.2020.
//

#include "elephantman.h"

ElephantMan::ElephantMan(int x, int y) : Rider() {
    this->x = x;
    this->y = y;
    this->damage.setValue(7);
    this->armor.setValue(3);
}

char ElephantMan::getType() {
    return 'E';
}
