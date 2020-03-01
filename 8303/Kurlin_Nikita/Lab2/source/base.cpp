#include "base.h"
#include "gamefield.h"

Base::Base(int maxUnitsCount, int health, int xx, int yy, GameField* field) : unitCount(0), maxCount(maxUnitsCount), health(health),
    x(xx), y(yy), field(field)
{
    units = new CompositeUnit();
}

void Base::createUnit(std::string unitName)
{
    if ((maxCount > unitCount) && (unitName == unitsNames[0] || unitName == unitsNames[1] || unitName == unitsNames[2]
                                   || unitName == unitsNames[3] || unitName == unitsNames[4] || unitName == unitsNames[5])){
        Unit* unit = nullptr;
        if (unitName == "Flatbow"){
            unit = ArchersFactory().createWeak();
        }
        else if (unitName == "Longbow"){
            unit = ArchersFactory().createStrong();
        }
        else if (unitName == "Dragoon"){
            unit = CavalryFactory().createStrong();
        }
        else if (unitName == "Hussar"){
            unit = CavalryFactory().createWeak();
        }
        else if (unitName == "Swordsman"){
            unit = InfantryFactory().createStrong();
        }
        else if (unitName == "Spearman"){
            unit = InfantryFactory().createWeak();
        }

        if (field->addUnit(unit, x - 1, y - 1)){}
        else if (field->addUnit(unit, x, y - 1)){}
        else if (field->addUnit(unit, x + 1, y - 1)){}
        else if (field->addUnit(unit, x - 1, y)){}
        else if (field->addUnit(unit, x + 1, y)){}
        else if (field->addUnit(unit, x - 1, y + 1)){}
        else if (field->addUnit(unit, x, y + 1)){}
        else if (field->addUnit(unit, x + 1, y + 1)){}
        else{
            delete unit;
            return;
        }

        units->addUnit(unit);
        unit->addObserver(this);
        unitCount++;

        if (unit->armyType == "Infantry")   //Для проверки удаления юнитов
            unit->deapth();                 //
    }
}

void Base::deleteUnit(Unit *unit)
{
    field->deleteUnit(unit);
    units->deleteUnit(unit);
    unit->deleteObserver(this);
    unitCount--;

}

void Base::printAll() const
{
    units->printAll();
}

void Base::update(Subject* subject)
{
    deleteUnit(static_cast<Unit *>(subject));
}
