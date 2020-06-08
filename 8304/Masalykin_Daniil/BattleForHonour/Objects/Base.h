#ifndef BATTLEFORHONOUR_BASE_H
#define BATTLEFORHONOUR_BASE_H

#include "../Armor/Armor.h"
#include "GameObject.h"
#include "Unit.h"
#include "../Observers/Observers.h"
#include <vector>
#include <iostream>
#include <algorithm>


class Base: public GameObject, public UnitObserver {

private:

    std::vector<BaseObserver*> baseObservers;

protected:

    void print(std::ostream &stream) const override;

public:

    Base(int health, Armor &armor):
        GameObject(ObjectType::BASE),
        health(health),
        armor(armor) {}

    bool addUnit(Unit *unit, Point position);
    void addObserver(BaseObserver *baseObserver);

    [[nodiscard]] int getHealth() const{
        return health;
    }
    Armor& getArmor(){
        return armor;
    }
    [[nodiscard]] int getMaxObjectsCount() const{
        return limit;
    }

    template <typename Type>
    Type *createUnit(Point position);
    void onUnitAttack(Unit *unit, Unit *other) override;
    void onUnitMove(Unit *unit, Point p) override;
    void onUnitDestroy(Unit *unit) override;
    void onUnitDamaged(Unit *unit) override;
    void onUnitHeal(Unit *unit) override;

private:
    std::vector<Unit*> units;
    int health;
    const int limit = 10;
    Armor &armor;
};

template<typename Type>
Type *Base::createUnit(Point position) {
    if (units.size() < limit) {
        Type *unit = new Type();
        units.push_back(unit);
        unit->addObserver(this);

        for (auto elem:baseObservers)
            elem->onBaseNewUnit(unit, position);

        Log::log << "[#Base] Unit created\n";

        return unit;
    } else{
        Log::log << "[#Base] Cannot create unit. Limit is exceeded.\n";
        return nullptr;
    }
}

#endif //BATTLEFORHONOUR_BASE_H
