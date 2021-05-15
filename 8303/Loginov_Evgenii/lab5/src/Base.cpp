//
// Created by Evgeniy on 3/8/2020.
//

#include "Base.h"
#include "Field.h"

Base::Base(Field *field, int x, int y, int maxCountUnit, int health) :
    field(field),
    x(x), y(y),
    maxCountUnit(maxCountUnit),
    health(health),
    countUnit(0)
{
}

Unit* Base::createUnit(char name)
{
    if(countUnit<maxCountUnit) {
        Unit* unit = unitFactory.createUnit(name, x,y);
        if(!unit) {
            std::cout << "Can't create!" << std::endl;
            return nullptr;
        }

        countUnit++;

        units.addUnit(unit);
        unitsAtBase.addUnit(unit);

        unit->addObserver(this); // Добавляем текущую базу как наблюдателя

        this->field->adapter->createUnit(unit);
        return unit;
    }

    return nullptr;
}

void Base::printInfo()
{
    std::cout << "Base Info: " << std::endl;
    std::cout << "----------" << std::endl;

    std::cout << "maxCountUnit: " << maxCountUnit << std::endl;
    std::cout << "countUnit: " << countUnit << std::endl;
    std::cout << "health: " << health << std::endl;

    printUnits();
    std::cout << "----------" << std::endl;
}

void Base::printUnits()
{
    std::cout << "Units at base now: " << std::endl;
    unitsAtBase.print();

    std::cout << "All units from this base: " << std::endl;
    units.print();

}

bool Base::isUnitAtBase(Unit *unit)
{
    for(const auto& u: unitsAtBase.unitsGroup) {
        if(u==unit)
            return true;
    }
    return false;
}

void Base::exitBase(Unit *unit)
{
    field->addUnit(unit);
    std::cout << "exit base" << std::endl;
    unitsAtBase.removeUnit(unit);
    countUnit--;
}

void Base::enterBase(Unit *unit)
{
    std::cout << "enter base" << std::endl;
    unitsAtBase.addUnit(unit);
    countUnit++;
}

Unit *Base::getUnitById(int id)
{
    if(id>=0 && id<units.unitsGroup.size())
        return units.unitsGroup.at(id);
    else {
        std::cout << "No unit with this id " << id << std::endl;
        return nullptr;
    }
}

void Base::update(SubjectObserve *subject) {
    Unit *unit = static_cast<Unit*>(subject);
    units.removeUnit(unit);
    unitsAtBase.removeUnit(unit);
    field->removeUnit(unit);
}

std::ostream& operator<< (std::ostream &out, const Base& base)
{
    //out << " x: " << base.x << ",  y: " << base.y << ", health: " << base.health << ", max count unit: " << base.maxCountUnit;
    //out << "maxCountUnit: " << base.maxCountUnit;
    return out;
}
