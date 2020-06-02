#pragma once
#include <unitsinterface.h>

class DamageAbsorberInfantry : public UnitDamageAbsorberInterface, public InfantryInterface
{
public:
    DamageAbsorberInfantry(Type type);
    QString getClass() override;

    CreatureInterface* copy() override
    {
        return new DamageAbsorberInfantry(*this);
    }
    UnitType getType() const override
    {
        return DMG_ABS_INF;
    }
};


class CritInfantry : public InfantryInterface, public UnitCritInterface
{
public:
    CritInfantry(Type type);
    QString getClass() override;

    CreatureInterface* copy() override
    {
        return new CritInfantry(*this);
    }
    UnitType getType() const override
    {
        return CRT_DMG_INF;
    }

};


class DamageAbsorberCavalry : public CavalryInterface, public UnitDamageAbsorberInterface
{
public:
    DamageAbsorberCavalry(Type type);
    QString getClass() override;

    CreatureInterface* copy() override
    {
        return new DamageAbsorberCavalry(*this);
    }
    UnitType getType() const override
    {
        return DMG_ABS_CAV;
    }
};


class CritCavalry : public CavalryInterface, public UnitCritInterface
{
public:
    CritCavalry(Type type);
    QString getClass() override;

    CreatureInterface* copy() override
    {
        return new CritCavalry(*this);
    }
    UnitType getType() const override
    {
        return CRT_DMG_CAV;
    }
};


class DamageAbsorberArcher : public ArcherInterface, public UnitDamageAbsorberInterface
{
public:
    DamageAbsorberArcher(Type type);
    QString getClass() override;

    CreatureInterface* copy() override
    {
        return new DamageAbsorberArcher(*this);
    }
    UnitType getType() const override
    {
        return DMG_ABS_ARC;
    }
};

class CritArcher : public ArcherInterface, public UnitCritInterface
{
public:
    CritArcher(Type type);
    QString getClass() override;

    CreatureInterface* copy() override
    {
        return new CritArcher(*this);
    }
    UnitType getType() const override
    {
        return CRT_DMG_ARC;
    }
};
