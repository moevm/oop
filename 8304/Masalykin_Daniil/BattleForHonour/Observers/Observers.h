#ifndef BATTLEFORHONOUR_OBSERVERS_H
#define BATTLEFORHONOUR_OBSERVERS_H

#include "../Objects/Unit.h"
#include "../GameField/Point.h"

class Unit;

class UnitObserver {

public:

    virtual void onUnitAttack(Unit *unit, Unit *other) = 0;
    virtual void onUnitMove(Unit *unit, Point p) = 0;
    virtual void onUnitDestroy(Unit *unit) = 0;
    virtual void onUnitHeal(Unit *unit) = 0;
    virtual void onUnitDamaged(Unit *unit) = 0;

};

class BaseObserver {

public:
    virtual void onBaseNewUnit(Unit *unit, Point position) = 0;
};


#endif //BATTLEFORHONOUR_OBSERVERS_H
