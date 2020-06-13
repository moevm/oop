//
// Created by anton on 16.02.2020.
//

#include "Cell.h"

Cell::Cell(): unit(nullptr){}

void Cell::clearCell() {
    unit = nullptr;
}

void Cell::setCharacter(Unit* newUnit) {
    if(unit == nullptr)
        unit = newUnit;
}

void Cell::setLandscape(Landscape *landscape) {
    this->landscape = landscape;
}

void Cell::setBase(Base *base) {
    if(base == nullptr)
        this->base = base;
}

Unit* Cell::getCharacter() const{
    return this->unit;
}



Cell::Cell(const Cell& obj):Cell()
{
    this->unit = obj.unit;
}

Cell& Cell::operator=(const Cell& obj) {
    if(this == &obj)
        return *this;
    this->unit = obj.unit;
    return *this;
}

bool Cell::isAvailable(const Unit* tmp) const
{
    printf("unit(%c) landscape(%c) available(%d)\n",tmp->getClass(),landscape->getType(), landscape->isAvailable(tmp));
    return (!unit && !base && landscape->isAvailable(tmp));
}

Landscape* Cell::getLandscape() const
{
    return this->landscape;
}

Neutral* Cell::getNeutral() const
{
    return this->neutral;
}

void Cell::setNeutral(Neutral *tmp) {
    this->neutral = tmp;
}