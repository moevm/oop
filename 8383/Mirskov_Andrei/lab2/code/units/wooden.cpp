//
// Created by andrei on 19.02.2020.
//

#include "wooden.h"

WoodenArcher::WoodenArcher(Base *base) : Archer() {
    this->damage.setValue(1);
    this->armor.setValue(2);
    this->view = base;
}

char WoodenArcher::getType() {
    return 'W';
}

void WoodenArcher::notify() {
    this->view->update(this);
}

int WoodenArcher::getBaseNum() {
    return this->view->getNum();
}

WoodenArcher::~WoodenArcher() {
    this->notify();
    this->view = nullptr;
}
