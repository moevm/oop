//
// Created by andrei on 19.02.2020.
//

#include "horseman.h"

HorseMan::HorseMan(int x, int y) : Rider() {
    this->x = x;
    this->y = y;
    this->damage.setValue(3);
    this->armor.setValue(2);
}

char HorseMan::getType() {
    return 'H';
}
