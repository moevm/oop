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
};

#endif //OOP_1_FABRIC_H
