//
// Created by anton on 11.03.2020.
//

#ifndef OOP_1_FABRIC_H
#define OOP_1_FABRIC_H

#include "Units/Unit.h"
#include "Units/Elf.h"
#include "Units/Bard.h"
#include "Units/Flamen.h"
#include "Units/Necromancer.h"
#include "Units/Dwarf.h"
#include "Units/Paladin.h"

class Unit;

class Fabric {
public:
    virtual Unit* createFirstType() = 0;

    virtual Unit* createSecondType() = 0;

    virtual Unit* createFirstType(Specifications) = 0;

    virtual Unit* createSecondType(Specifications) = 0;
};

class ThiefFabric:public Fabric
{
public:
    Elf* createFirstType() override
    {
        return new Elf();
    }
    Bard* createSecondType() override
    {
        return  new Bard();
    }

    Elf* createFirstType(Specifications loaded) override
    {
        return new Elf(loaded);
    }

    Bard* createSecondType(Specifications loaded) override
    {
        return  new Bard(loaded);
    }
};

class WizardFabric: public Fabric
{
public:
    Flamen* createFirstType() override
    {
        return new Flamen();
    }

    Necromancer* createSecondType() override
    {
        return new Necromancer();
    }

    Flamen* createFirstType(Specifications loaded) override
    {
        return new Flamen(loaded);
    }

    Necromancer* createSecondType(Specifications loaded) override
    {
        return  new Necromancer(loaded);
    }
};

class WarriorFabric: public Fabric
{
public:
    Dwarf* createFirstType() override
    {
        return new Dwarf();
    }

    Paladin* createSecondType() override
    {
        return new Paladin();
    }

    Dwarf* createFirstType(Specifications loaded) override
    {
        return new Dwarf(loaded);
    }

    Paladin* createSecondType(Specifications loaded) override
    {
        return  new Paladin(loaded);
    }
};

class TitansFabric
{
public:
    Unit* createUnit(char unitClass, Specifications values)
    {
        Unit* newUnit = nullptr;
        switch (unitClass)
        {
            case 'b':
                newUnit = ThiefFabric().createSecondType(values);
                break;
            case 'd':
                newUnit = WarriorFabric().createFirstType(values);
                break;
            case 'e':
                newUnit = ThiefFabric().createFirstType(values);
                break;
            case 'f':
                newUnit = WizardFabric().createFirstType(values);
                break;
            case 'n':
                newUnit = WizardFabric().createSecondType(values);
                break;
            case 'p':
                newUnit = WarriorFabric().createSecondType(values);
                break;
            default:
                throw LogicException("non-exist unit class", std::to_string(unitClass));
        }
        return newUnit;
    }
};

#endif //OOP_1_FABRIC_H
