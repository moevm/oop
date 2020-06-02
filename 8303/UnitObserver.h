//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_UNITOBSERVER_H
#define OOP_LAB1_UNITOBSERVER_H

class Unit;

class UnitObserver {

public:

    virtual void onUnitAttack(Unit *unit, Unit *other)=0;
    virtual void onUnitMove(Unit *unit, Point p)=0;
    virtual void onUnitDestroy(Unit *unit)=0;
    virtual void onUnitDamaged(Unit *unit)=0;
    virtual void onUnitHeal(Unit *unit)=0;

};


#endif //OOP_LAB1_UNITOBSERVER_H
