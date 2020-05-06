#pragma once

#include "Unit.h"


class SiegeEngine : public Unit
{
public:
    SiegeEngine(Point point, Base* base);
    uint8_t getUnitClass() override;
    double classAttackModifier(Object* enemy) override;
};



class Catapult : public SiegeEngine
{
public:
    Catapult(Point point, Base* base);
    ~Catapult();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class Ram : public SiegeEngine
{
public:
    Ram(Point point, Base* base);
    ~Ram();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};
