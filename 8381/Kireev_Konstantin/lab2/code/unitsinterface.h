#pragma once
#include <field.h>
#include <cellInterface.h>

class InfantryInterface : public virtual UnitInterface //интерфейс пехоты
{
};

class ArcherInterface : public virtual UnitInterface  //интерфецс лучников
{
};

class CavalryInterface : public virtual UnitInterface  //интерфейс конницы
{
};

class UnitCritInterface : public virtual UnitInterface //интерфейс для юнитов с критическим уроном
{
protected:
    double critFactor;
public:
    void takeDamage(int damage) override
    {
        int healthValue = health->getValue();
        healthValue = (healthValue - (damage - 20 * armor->getValue()));
        this->setHealth(healthValue);
    }
};

class UnitDamageAbsorberInterface : public virtual UnitInterface //интерфейс для юнитов с поглощением урона
{
protected:
    double absorptionFactor;
public:
    void takeDamage(int damage) override {
        int healthValue = health->getValue();
        healthValue = (healthValue - (damage - 20 * armor->getValue())) * (1 - absorptionFactor);

        this->setHealth(healthValue);
    }
};
