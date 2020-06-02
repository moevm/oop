#pragma once
#include "interfacesforobjects.h"

class InfantryInterface : public virtual UnitInterface
{

};


class CavalryInterface : public virtual UnitInterface
{

};


class ArcherInterface : public virtual UnitInterface
{

};


class CritDealerInterface : public virtual UnitInterface
{
protected:
    double critFactor;
public:
    void takeDamage(int damage) override
    {
        int healthValue = health->getValue();
        healthValue = (healthValue - (damage - armor->getValue()));
        this->setHealth(healthValue);
    }
};


class DamageAbsorberInterface : public virtual UnitInterface
{
protected:
    double absorbtionCoefficient;
public:
    void takeDamage(int damage) override
    {
        int healthValue = health->getValue();
        healthValue = (healthValue - (damage - armor->getValue())) * (1 - absorbtionCoefficient);

        this->setHealth(healthValue);
    }
};
