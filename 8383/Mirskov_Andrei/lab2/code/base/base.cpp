//
// Created by andrei on 02.03.2020.
//

#include "base.h"
#include "../vector/vector.cpp"

Base::Base(int baseNum, int health) {
    this->health = health;
    this->baseNum = baseNum;
}

Unit* Base::createUnit(char type) {
    if (this->onView.getSize() == maxUnit) return nullptr;

    Unit* newUnit = Factory::createUnit(this, type);
    this->onView.push(newUnit);
    return newUnit;
}

void Base::update(Unit *unit) {
    for (int i = 0; i < this->onView.getSize(); i++) {
        if (this->onView[i] == unit) {
            this->onView.remove(i);
            return;
        }
    }
}

int Base::getNum() {
    return this->baseNum;
}

void Base::takeDamage(int damage) {
    this->health -= damage;

}
