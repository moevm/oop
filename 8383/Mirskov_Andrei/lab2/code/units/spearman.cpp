//
// Created by andrei on 19.02.2020.
//

#include "spearman.h"

SpearMan::SpearMan(int x, int y) : Infantry() {
    this->x = x;
    this->y = y;
    this->damage.setValue(4);
    this->armor.setValue(5);
}

char SpearMan::getType() {
    return 'M';
}
