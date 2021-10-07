//
// Created by andrei on 04.04.2020.
//

#include "cell.h"
#include "iostream"

Cell::Cell() {
    this->landscape = new Ground;
}

Landscape *Cell::getLandscape() {
    return this->landscape;
}

Unit *Cell::getUnit() {
    return this->unit;
}

Neutral *Cell::getNeutral() {
    return this->neutral;
}

void Cell::setUnit(Unit *newUnit) {
    this->unit = newUnit;
}

void Cell::setNeutral(Neutral *newNeutral) {
    this->neutral = newNeutral;
}

bool Cell::isUnit() {
    return this->unit != nullptr;
}

bool Cell::isNeutral() {
    return this->neutral != nullptr;
}

Base *Cell::getBase() {
    return this->base;
}

void Cell::setBase(Base *newBase) {
    this->base = newBase;
}

bool Cell::isBase() {
    return this->base != nullptr;
}
