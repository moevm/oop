//
// Created by andrei on 19.02.2020.
//

#include "horseman.h"

HorseMan::HorseMan(Base *base) : Rider() {
    this->damage.setValue(3);
    this->armor.setValue(2);
    this->view = base;
}

char HorseMan::getType() {
    return 'H';
}

void HorseMan::notify() {
    this->view->update(this);
}

int HorseMan::getBaseNum() {
    return this->view->getNum();
}

HorseMan::~HorseMan() {
    this->notify();
    this->view = nullptr;

}
