//
// Created by anton on 11.04.2020.
//

#include "Adapter.h"

void Adapter::attack(Unit* unit, int damage) {
    print("Unit " +  unit->getName() + " get " + std::to_string(damage) + " damage\n" );
}

void Adapter::setBase(Base *base) {
    std::ostringstream stream;
    stream << *base;
    print("set " + stream.str());
}

void Adapter::deleteUnit(Unit *unit) {
    print("Unit " + unit->getName() + " deleted\n");
}

void Adapter::setUnit(Unit *unit) {
    std::ostringstream stream;
    stream << *unit;
    print(stream.str() );
}

void Adapter::move(Unit* unit) {
    print("Unit " + unit->getName() + " moved to " + std::to_string(unit->getX()) + ", " + std::to_string(unit->getY()) + "\n");
}

void Adapter::logChanged(std::string mode) {
    print("log changed to " + mode + " stream\n");
}