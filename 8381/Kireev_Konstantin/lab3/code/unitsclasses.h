#pragma once
#include <unitsinterface.h>

class AbsorbInfantry : public DamageAbsorberInterface, public InfantryInterface
{
public:
    AbsorbInfantry(unsigned int possessorId);
    QString getClass() override;
    CreatureInterface* copy() override { return new AbsorbInfantry(*this); }
    UnitType getType() const override { return ABSORB_INFANTRY; }
};


class CritInfantry : public InfantryInterface, public CritDealerInterface
{
public:
    CritInfantry(unsigned int possessorId);
    QString getClass() override;
    CreatureInterface* copy() override { return new CritInfantry(*this); }
    UnitType getType() const override { return CRIT_INFANTRY; }

};


class AbsorbCavalry : public CavalryInterface, public DamageAbsorberInterface
{
public:
    AbsorbCavalry(unsigned int possessorId);
    QString getClass() override;
    CreatureInterface* copy() override { return new AbsorbCavalry(*this); }
    UnitType getType() const override { return ABSORB_CAVALRY; }
};


class CritCavalry : public CavalryInterface, public CritDealerInterface
{
public:
    CritCavalry(unsigned int possessorId);
    QString getClass() override;
    CreatureInterface* copy() override { return new CritCavalry(*this); }
    UnitType getType() const override { return CRIT_CAVALRY; }
};


class AbsorbArcher : public ArcherInterface, public DamageAbsorberInterface
{
public:
    AbsorbArcher(unsigned int possessorId);
    QString getClass() override;
    CreatureInterface* copy() override { return new AbsorbArcher(*this); }
    UnitType getType() const override { return ABSORB_ARCHER; }
};

class CritArcher : public ArcherInterface, public CritDealerInterface
{
public:
    CritArcher(unsigned int possessorId);
    QString getClass() override;
    CreatureInterface* copy() override { return new CritArcher(*this); }
    UnitType getType() const override { return CRIT_ARCHER; }
};
