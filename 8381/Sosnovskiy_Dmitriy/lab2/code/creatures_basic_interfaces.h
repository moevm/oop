#pragma once
#include "iprintable.h"
#include "attribute.h"
#include "fieldcomponent_creature_observer_interfaces.h"
#include "base_unit_observer_interfaces.h"

class IUnit;
class INeutralObject;
class INeutralObjectsEffectStrategy;

//basic creature interface

enum CreatureType { BASE, UNIT };
enum Race { DWARF, ELF };
class ICreature : public IPrintable, public ICreatureObservableByFieldComponent
{
protected:
    Attribute* health;
    Race race;
public:
    virtual ICreature* copy() = 0;
    virtual bool isMoveable() = 0;
    virtual CreatureType getCreatureType() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual void setHealth(int newHealth) = 0;

    void attachFieldComponent(ICreatureObserver* fieldComponent) override
    { this->fieldComponentAttachedTo = fieldComponent; }

    Race getRace() const { return this->race; }

    Attribute getHealth() const { return *health; }
};

//neutral objects base interfaces
class INeutralObject : public IPrintable
{
protected:
    INeutralObjectsEffectStrategy* strategy;
public:
    virtual ~INeutralObject() { delete strategy; }
    virtual void influenceOnUnit(IUnit* unit) = 0;
    virtual INeutralObject* copy() = 0;
};

//units basic interface
enum UnitType { ABSORB_INFANTRY, ABSORB_CAVALRY, ABSORB_ARCHER,
                CRIT_INFANTRY, CRIT_CAVALRY, CRIT_ARCHER };

class IUnit : public ICreature, public IUnitObservableByBase
{
protected:
    Attribute* armor;
    Attribute* damage;

public:

    virtual UnitType getType() const = 0;

    void attachBase(IUnitObserver* base) override { this->base = base; }

    bool isMoveable() override { return true; }

    CreatureType getCreatureType() const override { return UNIT; }

    void setHealth(int newHealth) override {
        health->setValue(newHealth);
        if(newHealth <= 0)
        {
            base->onUnitDestroyed(this);
            fieldComponentAttachedTo->onCreatureDestroyed();
        }
    }

    Attribute* getArmor() const { return armor; }
    void setArmor(int newArmor){
        *armor = newArmor;
    }

    Attribute* getDamage() const { return damage; }
    void setDamage(int newDamage){
        *damage = newDamage;
    }

    void setAllAttribues(int health, int armor, int damage){
        this->health->setValue(health);
        this->armor->setValue(armor);
        this->damage->setValue(damage);
    }

    void commitAttack(ICreature* attackedUnit);

    void clearNeutralObjectEffect()
    {
        health->setBonus(0);
        armor->setBonus(0);
        damage->setBonus(0);
    }

    IUnit& operator+=(INeutralObject* neutralObject){
        neutralObject->influenceOnUnit(this);
        return *this;
    }
};

