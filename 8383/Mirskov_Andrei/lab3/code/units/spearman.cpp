//
// Created by andrei on 19.02.2020.
//

#include "spearman.h"

SpearMan::SpearMan(Base *base) : Infantry() {
    this->damage.setValue(4);
    this->armor.setValue(5);
    this->view = base;
}

char SpearMan::getType() {
    return 'M';
}

void SpearMan::notify() {
    this->view->update(this);
}

int SpearMan::getBaseNum() {
    return this->view->getNum();
}

SpearMan::~SpearMan() {
    this->notify();
    this->view = nullptr;

}
