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

void Base::createUnit(char name)
{
    if(countUnit<maxCountUnit) {
        Unit* unit = unitFactory.createUnit(name, x,y);
        countUnit++;

        unitsAtBase.push_back(unit);
    }
}

void Base::printUnits() const
{
    for(const auto& u: unitsAtBase) {
        u->print();
        std::cout << " ";
    }
}
