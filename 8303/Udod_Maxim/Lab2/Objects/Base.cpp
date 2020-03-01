//
// Created by shenk on 01.03.2020.
//

#include "Base.h"

bool Base::addUnit(Unit *unit, Point position) {
    if (units.size() < maxObjectsCount){

        units.push_back(unit);
        GameField::getInstance()->addObject(unit, position.x, position.y);
        maxObjectsCount++;
        return true;

    } else{

        return false;

    }
}

void Base::onUnitAttack(Unit *unit) {
    std::cout << "Base: Unit " << unit << " attack" << std::endl;
}

void Base::onUnitMove(Unit *unit) {

    std::cout << "Base: Unit " << unit << " moving" << std::endl;

}

void Base::onUnitDestroy(Unit *unit) {

    auto position = std::find(units.begin(), units.end(), unit);
    if (position != units.end()) {
        GameField::getInstance()->deleteObject(unit);
        units.erase(position); // Тут уже и удаление юнита.
        std::cout << "Base: Unit " << unit << " destroyed" << std::endl;
    } else{
        std::cout << "Called observer of base for unit don't belong to it" << std::endl;
    }

}

void Base::onUnitDamaged(Unit *unit) {

    std::cout << "Base: Unit " << unit << " damaged" << std::endl;

}

void Base::onUnitHeal(Unit *unit) {

    std::cout << "Base: Unit " << unit << " healed" << std::endl;

}
