//
// Created by andrei on 19.02.2020.
//

#include "firearcher.h"

FireArcher::FireArcher(Base *base) : Archer() {
    this->damage.setValue(5);
    this->armor.setValue(9);
    this->view = base;
}

char FireArcher::getType() {
    return 'F';
}

void FireArcher::notify() {
    this->view->update(this);
}

int FireArcher::getBaseNum() {
    return this->view->getNum();
}

FireArcher::~FireArcher() {
    this->notify();
    this->view = nullptr;
}
