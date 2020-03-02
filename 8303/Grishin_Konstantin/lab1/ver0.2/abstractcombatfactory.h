#ifndef ABSTRACTCOMBATFACTORY_H
#define ABSTRACTCOMBATFACTORY_H

#include <string>

#include "Units/melee.h"
#include "Units/nuker.h"
#include "Units/range.h"

class Cell;

class AbstractCombatFactory
{
public:
    virtual ~AbstractCombatFactory(){}

    virtual Barbarian* createBarbarian(Cell *cell, const std::string &weapon_name) = 0;
    virtual Archer* createArcher(Cell *cell, const std::string &weapon_name) = 0;
    virtual Berserker *createBerserker(Cell *cell, const std::string &weapon_name) = 0;
};


class NeutralCombatFactory : public AbstractCombatFactory
{
public:
    Barbarian * createBarbarian(Cell *cell, const std::string &weapon_name) override;
    Archer * createArcher(Cell *cell, const std::string &weapon_name) override;
    Berserker * createBerserker(Cell *cell, const std::string &weapon_name) override;
};


class BluCombatFactory : public AbstractCombatFactory
{
public:
    Barbarian * createBarbarian(Cell *cell, const std::string &weapon_name) override;
    Archer * createArcher(Cell *cell, const std::string &weapon_name) override;
    Berserker * createBerserker(Cell *cell, const std::string &weapon_name) override;
};


class RedCombatFactory : public AbstractCombatFactory
{
public:
    Barbarian * createBarbarian(Cell *cell, const std::string &weapon_name) override;
    Archer * createArcher(Cell *cell, const std::string &weapon_name) override;
    Berserker * createBerserker(Cell *cell, const std::string &weapon_name) override;
};

#endif // ABSTRACTCOMBATFACTORY_H
