//
// Created by andrei on 02.03.2020.
//

#include "mainUnit.h"

int MainUnit::getHealth() {
    return this->health.getValue();
}

int MainUnit::getArmor() {
    return this->armor.getValue();
}

int MainUnit::getDamage() {
    return this->damage.getValue();
}

int MainUnit::getX() {
    return this->x;
}

void MainUnit::setX(int newX) {
    this->x = newX;
}

int MainUnit::getY() {
    return this->y;
}

void MainUnit::setY(int newY) {
    this->y = newY;
}

void MainUnit::heal(int health) {
    if (this->health.getValue() + health > this->maxHealth) this->health.setValue(maxHealth);
    else this->health.setValue(this->health.getValue() + health);
}

void MainUnit::takeItem(Clothes* clothes) {
    this->setArmor(this->getArmor() + clothes->getArmor());
}

void MainUnit::takeItem(Potion* potion) {
    this->heal(potion->getHealth());
}

void MainUnit::takeItem(Weapon* weapon) {
    this->setDamage(this->getDamage() + weapon->getDamage());
}

void MainUnit::takeItem(Kit* kit) {
    this->setDamage(this->getDamage() + kit->getDamage());
    this->setArmor(this->getArmor() + kit->getArmor());
}

void MainUnit::setDamage(int damage) {
    this->damage.setValue(damage);
}

void MainUnit::setArmor(int armor) {
    this->armor.setValue(armor);
}

void MainUnit::operator+=(Neutral* neutral) {
    switch (neutral->getType()) {
        case 'c': {
            auto *clothes = new Clothes;
            this->takeItem(clothes);
        }
        case 'p': {
            auto *potion = new Potion;
            this->takeItem(potion);
        }
        case 'w': {
            auto *weapon = new Weapon;
            this->takeItem(weapon);
        }
        case 'k': {
            auto *kit = new Kit;
            this->takeItem(kit);
        }
    }
}

bool MainUnit::takeDamage(int damage) {
    if (this->armor.getValue() < damage) {
        this->health.setValue(this->health.getValue() - damage + this->armor.getValue());
        if (this->health.getValue() <= 0) {
            return true;
        }
    }
}
