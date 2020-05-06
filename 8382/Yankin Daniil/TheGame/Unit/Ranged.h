#pragma once

#include "Unit.h"


class Ranged : public Unit
{
public:
    Ranged(Point point, Base* base);
    uint8_t getUnitClass() override;
    double classAttackModifier(Object* enemy) override;
};



class Archer : public Ranged
{
public:
    Archer(Point point, Base* base);
    ~Archer();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class Crossbowman : public Ranged
{
public:
    Crossbowman(Point point, Base* base);
    ~Crossbowman();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class ScoutCavalry : public Ranged
{
public:
    ScoutCavalry(Point point, Base* base);
    ~ScoutCavalry();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};
