#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include <unitsclasses.h>

class AbstractFactory //абстрактная фабрика
{
public:
    virtual ~AbstractFactory() = default;
    virtual InfantryInterface* createInfantry() const = 0;
    virtual CavalryInterface* createCavalry() const = 0;
    virtual ArcherInterface* createArcher() const = 0;
};

class CritUnitsFactory : public AbstractFactory //конкретная фабрика, поставляющая юнитов с критическим уроном
{
public:
    InfantryInterface* createInfantry() const override { return new CritInfantry; }
    CavalryInterface* createCavalry() const override { return new CritCavalry; }
    ArcherInterface* createArcher() const override { return new CritArcher; }
};

class DamageAbsorberUnitsFactory : public AbstractFactory //конкретная фабрика, поставляющая юнитов с поглощением урона
{
public:
    InfantryInterface* createInfantry() const override { return new DamageAbsorberInfantry; }
    CavalryInterface* createCavalry() const override { return new DamageAbsorberCavalry; }
    ArcherInterface* createArcher() const override { return new DamageAbsorberArcher; }
};

#endif // ABSTRACTFACTORY_H
