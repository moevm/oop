//
// Created by anton on 16.02.2020.
//

#include "Cell.h"

Cell::Cell():Object(nullptr){}

void Cell::clearCell() {
    Object = nullptr;
}

void Cell::setCharacter(Unit* newUnit) {
    if(Object == nullptr)
        Object = newUnit;
}

Unit* Cell::getCharacter() const{
    return this->Object;
}

Cell::Cell(const Cell& obj):Cell()
{
    this->Object = obj.Object;
}

Cell& Cell::operator=(const Cell& obj) {
    if(this == &obj)
        return *this;
    this->Object = obj.Object;
    return *this;
}