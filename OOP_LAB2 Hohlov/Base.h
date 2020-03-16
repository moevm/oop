//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_BASE_H
#define OOP_LAB1_BASE_H
#include "Armor.h"
#include "GameObject.h"
#include "UnitObserver.h"
#include "BaseObserver.h"

#include <vector>
#include <iostream>
#include <algorithm>

class Base: public GameObject, public UnitObserver {

private:

    std::vector<BaseObserver*> baseObservers;

protected:

    void print(std::ostream &stream) const override;

public:

    Base(int health, Armor &armortype): GameObject(ObjectType::BASE, health(health), armor(armortype)) {}
    bool addUnit(Unit *unit, Point position);
    void addObserver(BaseObserver *baseObserver);

    template <typename T>
    T *createUnit(Point position);

    void onUnitAttack(Unit *unit, Unit *other) override;
    void onUnitMove(Unit *unit, Point p) override;
    void onUnitDestroy(Unit *unit) override;
    void onUnitDamaged(Unit *unit) override;
    void onUnitHeal(Unit *unit) override;

private:

    std::vector<Unit*> units;

    int health;
    const int maxObjectsCount = 5;
    Armor &armor;

};

template<typename T>
T *Base::createUnit(Point position) {
    if (units.size() < maxObjectsCount) {
        T *unit = new T();
        units.push_back(unit);
        unit->addObserver(this);

        for (auto bo:baseObservers) bo->onBaseNewUnitCreated(unit, position);

        return unit;
    } else{

        std::cout << "Base: Cannot create unit. Limit is exceeded." << std::endl;

    }
}
#endif //OOP_LAB1_BASE_H
