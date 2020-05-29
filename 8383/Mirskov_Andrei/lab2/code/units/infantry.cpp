//
// Created by andrei on 19.02.2020.
//

#include "infantry.h"

Infantry::Infantry() : MainUnit() {
    this->maxHealth = 100;
    this->health.setValue(maxHealth);
}