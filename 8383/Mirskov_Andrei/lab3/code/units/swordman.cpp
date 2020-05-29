//
// Created by andrei on 19.02.2020.
//

#include "swordman.h"

SwordMan::SwordMan(Base *base) : Infantry() {
    this->damage.setValue(50);
    this->armor.setValue(3);
    this->view = base;
}

char SwordMan::getType() {
    return 'S';
}

void SwordMan::notify() {
    this->view->update(this);
}

int SwordMan::getBaseNum() {
    return this->view->getNum();
}

SwordMan::~SwordMan() {
    this->notify();
    this->view = nullptr;

}
