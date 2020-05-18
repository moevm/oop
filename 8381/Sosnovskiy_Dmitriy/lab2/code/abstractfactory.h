#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include "concrete_units_classes.h"

class AbstractUnitFactory
{
public:
    virtual ~AbstractUnitFactory() = default;
    virtual IInfantry* createInfantry(Race race) const = 0;
    virtual ICavalry* createCavalry(Race race) const = 0;
    virtual IArcher* createArcher(Race race) const = 0;
};


class CritDealersFactory : public AbstractUnitFactory {
public:
    IInfantry* createInfantry(Race race) const override { return new CritInfantry(race); }
    ICavalry* createCavalry(Race race) const override { return new CritCavalry(race); }
    IArcher* createArcher(Race race) const override { return new CritArcher(race); }
};

class AbsorbersFactory : public AbstractUnitFactory {
public:
    IInfantry* createInfantry(Race race) const override { return new AbsorbInfantry(race); }
    ICavalry* createCavalry(Race race) const override { return new AbsorbCavalry(race); }
    IArcher* createArcher(Race race) const override { return new AbsorbArcher(race); }
};

#endif // ABSTRACTFACTORY_H
