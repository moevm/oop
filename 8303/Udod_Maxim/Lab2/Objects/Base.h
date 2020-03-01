//
// Created by shenk on 01.03.2020.
//

#ifndef UNTITLED13_BASE_H
#define UNTITLED13_BASE_H

#include "../Armor/Armor.h"
#include "GameObject.h"
#include "Units/Wizard/FireMage.h"
#include "Units/Wizard/Voldemort.h"
#include <vector>
#include "../GameField//GameField.h"
#include "../UnitObserver.h"
#include <iostream>
#include <algorithm>

class Base: public GameObject, public UnitObserver {

public:

    Base(): GameObject(ObjectType::BASE) {}
    bool addUnit(Unit *unit, Point position);

    template <typename T>
    T *createUnit(Point position);

    void onUnitAttack(Unit *unit) override;
    void onUnitMove(Unit *unit) override;
    void onUnitDestroy(Unit *unit) override;
    void onUnitDamaged(Unit *unit) override;
    void onUnitHeal(Unit *unit) override;

private:

    std::vector<Unit*> units;

    int health;
    int maxObjectsCount = 5;
    Armor armor;

};

template<typename T>
T *Base::createUnit(Point position) {
    if (units.size() < maxObjectsCount) {
        T *unit = new T();
        units.push_back(unit);
        unit->addObserver(this);
        GameField::getInstance()->addObject(unit, position.x, position.y);

        maxObjectsCount++;
        return unit;
    } else{

        std::cout << "Base: Cannot create unit. Limit is exceeded." << std::endl;

    }
}

#endif //UNTITLED13_BASE_H
