#pragma once
#include <unitsinterface.h>

class DamageAbsorberInfantry : public InfantryInterface, public UnitDamageAbsorberInterface //пехота, поглощающая урон
{
public:
    DamageAbsorberInfantry();
    QString getClass() override;
    cellInterface* copy() override { return new DamageAbsorberInfantry(*this); }
};

class CritInfantry : public InfantryInterface, public UnitCritInterface //пехота, с критическим уроном
{
public:
    CritInfantry();
    QString getClass() override;
    cellInterface* copy() override { return new CritInfantry(*this); }
};

class DamageAbsorberCavalry : public CavalryInterface, public UnitDamageAbsorberInterface //конница, поглощающая урон
{
public:
    DamageAbsorberCavalry();
    QString getClass() override;
    cellInterface* copy() override { return new DamageAbsorberCavalry(*this); }
};

class CritCavalry : public CavalryInterface, public UnitCritInterface //конница, с критическим уроном
{
public:
    CritCavalry();
    QString getClass() override;
    cellInterface* copy() override { return new CritCavalry(*this); }
};

class DamageAbsorberArcher : public ArcherInterface, public UnitDamageAbsorberInterface //лучники, поглощающие урон
{
public:
    DamageAbsorberArcher();
    QString getClass() override;
    cellInterface* copy() override { return new DamageAbsorberArcher(*this); }
};

class CritArcher : public ArcherInterface, public UnitCritInterface //лучники, с критическим уроном
{
public:
    CritArcher();
    QString getClass() override;
    cellInterface* copy() override { return new CritArcher(*this); }
};
