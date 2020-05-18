#pragma once
#include "field.h"
#include "abstractfactory.h"
#include "base_unit_observer_interfaces.h"

class Base : public ICreature, public IUnitObserver
{
private:
    Field* field;

    AbstractUnitFactory* critDealersFactory = new CritDealersFactory();

    AbstractUnitFactory* absorbersFactory = new AbsorbersFactory();
public:    
    Base(Field* field, Race race) {
        this->field = field;
        switch (race) {
            case DWARF:
                field->placeCreature(0, 0, this);
                break;
            case ELF:
                field->placeCreature(field->getRowsAmount()-1, field->getColumnsAmount()-1, this);
                break;
        }
        this->race = race;
        this->health = new Attribute(100);
    }

    ~Base()
    {
        delete field;
        delete critDealersFactory;
        delete absorbersFactory;
    }

    QString getClass() override { return "Base"; }

    bool isMoveable() override { return false; }

    CreatureType getCreatureType() const override { return BASE; }

    void onUnitDestroyed(IUnit* destroyedUnit) override
    {
        delete destroyedUnit;
    }

    ICreature* copy() override { return new Base(*this); }

    void takeDamage(int damage) override {
        int healthValue = health->getValue();
        this->setHealth(healthValue - damage);
    }

    Attribute getHealth() const { return *health; }

    void setHealth(int newHealth) override {
        health->setValue(newHealth);
        if(newHealth <= 0) fieldComponentAttachedTo->onCreatureDestroyed();
    }

    void createUnit(UnitType unitType, unsigned int row, unsigned int column) {
        try {
            IUnit* unit;
            switch (unitType) {
                case CRIT_INFANTRY:
                    unit = critDealersFactory->createInfantry(race);
                    break;
                case CRIT_CAVALRY:
                    unit = critDealersFactory->createCavalry(race);
                    break;
                case CRIT_ARCHER:
                    unit = critDealersFactory->createArcher(race);
                    break;
                case ABSORB_INFANTRY:
                    unit = absorbersFactory->createInfantry(race);
                    break;
                case ABSORB_CAVALRY:
                    unit = absorbersFactory->createCavalry(race);
                    break;
                case ABSORB_ARCHER:
                    unit = absorbersFactory->createArcher(race);
                    break;
            }

            unit->attachBase(this);

            field->placeCreature(row, column, unit);

        } catch (...) {   }
    }
};

