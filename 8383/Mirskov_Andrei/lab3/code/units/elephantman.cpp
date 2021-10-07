//
// Created by andrei on 19.02.2020.
//

#include "elephantman.h"

ElephantMan::ElephantMan(Base *base) : Rider() {
    this->damage.setValue(7);
    this->armor.setValue(3);
    this->view = base;
}

char ElephantMan::getType() {
    return 'E';
}

void ElephantMan::notify() {
    this->view->update(this);
}

int ElephantMan::getBaseNum() {
    return this->view->getNum();
}

ElephantMan::~ElephantMan() {
    this->notify();
    this->view = nullptr;
}
