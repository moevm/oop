#pragma once

#include "Unit.h"


class Melee : public Unit
{
public:
    Melee(Point point, Base* base);
    uint8_t getUnitClass() override;
    double classAttackModifier(Object* enemy) override;
};



class Swordsman : public Melee
{
public:
    Swordsman(Point point, Base* base);
    ~Swordsman();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class Pikeman : public Melee
{
public:
    Pikeman(Point point, Base* base);
    ~Pikeman();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};


class ShockCavalry : public Melee
{
public:
    ShockCavalry(Point point, Base* base);
    ~ShockCavalry();
    uint8_t getObjectType() override;
    double typeAttackModifier(Object* enemy) override;
};
