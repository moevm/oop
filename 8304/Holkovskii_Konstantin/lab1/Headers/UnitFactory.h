#ifndef UNTITLED1_UNIT_FACTORY_H
#define UNTITLED1_UNIT_FACTORY_H

#endif //UNTITLED1_UNIT_FACTORY_H
#include "Unit.h"

struct UnitFactory
{
    virtual Unit* createType1() = 0;
    virtual Unit* createType2() = 0;
};

struct Tier1Factory : UnitFactory
{
    Tier1Factory() = default;

    Unit* createType1() override;
    Unit* createType2() override;
};

struct Tier2Factory : UnitFactory
{
    Tier2Factory() = default;

    Unit* createType1() override;
    Unit* createType2() override;
};

struct Tier3Factory : UnitFactory
{
    Tier3Factory() = default;

    Unit* createType1() override;
    Unit* createType2() override;
};

