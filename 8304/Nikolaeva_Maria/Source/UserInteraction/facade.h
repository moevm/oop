#ifndef FACADE_H
#define FACADE_H

#include "mediator.h"

#include "GameField/gamefield.h"

#include "Unit/unit.h"
#include "Unit/base/base.h"

#include <set>

#include <math.h>


class Facade
{
public:
    Facade(Mediator* mediator, Base* base,
           std::set<Unit* >* units,
           Base* enemyBase,
           GameField* gemaField);

    ~Facade();

    void charge();
    void deffend();
    bool createInfantryUnit();
    bool createStandingUnit();
    bool createFlyingUnit();

protected:
    bool attack(Unit* unit);
    void moveUnit(Unit* unit);

private:
    Base* base;
    Base* enemyBase;
    std::set<Unit* >* units;
    Mediator* mediator;
    GameField* gameField;
};

#endif // FACADE_H
