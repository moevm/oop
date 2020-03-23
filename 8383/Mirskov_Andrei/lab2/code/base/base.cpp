//
// Created by andrei on 02.03.2020.
//

#include "base.h"
#include "../vector/vector.cpp"

Base::Base(int x, int y, int health) {
    this->x = x;
    this->y = y;
    this->health = health;
}

void Base::addUnit(int x, int y, char type) {
    if (this->units.getSize() == maxUnit) return;

    for (int i = 0; i < this->units.getSize(); i++) {
        if (this->units[i]->getX() == x && this->units[i]->getY() == y) {
            this->removeUnit(x, y);
            break;
        }
    }
    this->units.push(Factory::createUnit(x, y, type));

}

void Base::removeUnit(int x, int y) {
    for (int i = 0; i < this->units.getSize(); i++) {
        if (this->units[i]->getX() == x && this->units[i]->getY() == y) {
            this->units.remove(i);
            break;
        }
    }
}

void Base::takeDamage(int damage) {
    this->health -= damage;
}

void Base::moveUnit(int x1, int y1, int x2, int y2) {
    for (int i = 0; i < this->units.getSize(); i++) {
        if (this->units[i]->getX() == x1 && this->units[i]->getY() == y1) {
            this->units[i]->setX(x2);
            this->units[i]->setY(y2);
        }
    }
}

void Base::takeItem(int x1, int y1, Neutral* neutral) {
    for (int i = 0; i < this->units.getSize(); i++) {
        if (this->units[i]->getX() == x1 && this->units[i]->getY() == y1) {
            *this->units[i] += neutral;
            break;
        }
    }
}

bool Base::isUnit(int x, int y) {
    for (int i = 0; i < this->units.getSize(); i++) {
        if (this->units[i]->getX() == x && this->units[i]->getY() == y) {
            return true;
        }
    }
    return false;
}

Unit *Base::getUnit(int x, int y) {
    for (int i = 0; i < this->units.getSize(); i++) {
        if (this->units[i]->getX() == x && this->units[i]->getY() == y) {
            return units[i];
        }
    }
}
