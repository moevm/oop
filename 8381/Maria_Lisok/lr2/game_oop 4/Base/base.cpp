#include "base.h"

Base::Base(int maxUnitsCount, int health, int xx, int yy, int baseNumb) : baseNumb(baseNumb),
    unitCount(0), maxCount(maxUnitsCount),
    unitCurr(0),health(health), x(xx), y(yy)
{
    units = new CompositeUnit();
}

int Base::getBaseNumb() const
{
    return baseNumb;
}

int Base::getX() const
{
    return x;
}

int Base::getY() const
{
    return y;
}

int Base::getUnitCount() const
{
    return unitCount;
}

int Base::getMaxCount() const
{
    return maxCount;
}

int Base::getHealth() const
{
    return health;
}

Unit *Base::createUnit(string unitName)
{
    AbstractArmy* humanityArmy = new HumanityArmy();
    AbstractArmy* creaturesArmy = new CreaturesArmy();
    Unit* unit = nullptr;
    if (unitName == "Archer"){
        unit = humanityArmy->createArrow();
    }
    else if (unitName == "Shaman"){
        unit = creaturesArmy->createArrow();
    }
    else if (unitName == "Knigth"){
        unit = humanityArmy->createCavelry();
    }
    else if (unitName == "Rider"){
        unit = creaturesArmy->createCavelry();
    }
    else if (unitName == "Swardman"){
        unit = humanityArmy->createInfantry();
    }
    else if (unitName == "Ork"){
        unit = creaturesArmy->createInfantry();
    }

    units->addUnit(unit);
    unitCount++;
    return unit;
}

void Base::addUnit(Unit *u)
{
    units->addUnit(u);
    unitCount++;
}

void Base::deleteUnit(Subject * unit)
{
    if (units->delUnit(unit)){
        unitCount--;
    }
}

Unit *Base::getCurrUnit()
{
    return units->getUnit(unitCurr);
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


