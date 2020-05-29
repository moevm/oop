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

void MainUnit::heal(int health) {
    if (this->health.getValue() + health > this->maxHealth) this->health.setValue(maxHealth);
    else this->health.setValue(this->health.getValue() + health);
}

void MainUnit::setDamage(int damage) {
    this->damage.setValue(damage);
}

void MainUnit::setArmor(int armor) {
    this->armor.setValue(armor);
}

void MainUnit::operator+=(Neutral* neutral) {
    neutral->use(this);
}

bool MainUnit::takeDamage(int damage) {
    if (this->armor.getValue() < damage) {
        this->health.setValue(this->health.getValue() - damage + this->armor.getValue());
        if (this->health.getValue() <= 0) {
            return true;
        }
    }
    return false;
}
