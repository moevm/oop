#include "base.h"
#include "gamefield.h"

Base::Base(int maxUnitsCount, int health, int xx, int yy, GameField* field) : unitCount(0), maxCount(maxUnitsCount), unitCurr(0),
    health(health), x(xx), y(yy), field(field)
{
    units = new CompositeUnit();
}

Unit* Base::createUnit(std::string unitName)
{
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

        units->addUnit(unit);
        unitCount++;
        return unit;
}

void Base::deleteUnit(Subject *unit)
{
    if (units->deleteUnit(unit)){
        unitCount--;
    }
}

void Base::printAll()
{
    Unit* currUnit;
    Point* currPoint;
    for (int i = 0; i < unitCount; i++){
        if (unitCurr >= units->unitsMas.size())
            unitCurr = 0;
        currUnit = units->unitsMas[unitCurr++];
        currPoint = field->findUnit(currUnit);
        std::cout << "\t" << currUnit->armyType << " (" << currPoint->x << ";" << currPoint->y << ") Health: " << currUnit->attributes->health << "\n";
    }
}

int Base::getCapacityCount()
{
    return maxCount - unitCount;
}

Unit* Base::getCurrUnit()
{
    if (unitCurr >= units->unitsMas.size())
        unitCurr = 0;
    return units->unitsMas[unitCurr++];
}

int Base::getX()
{
    return this->x;
}

int Base::getY()
{
    return this->y;
}

bool Base::getDamage(int numb)
{
    this->health -= numb;
    if (this->health <= 0){
        this->health = 0;
        return true;
    }
    return false;
}
