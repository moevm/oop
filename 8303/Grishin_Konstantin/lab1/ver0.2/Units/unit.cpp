#include "Units/unit.h"
#include "cell.h"

Unit::Unit(Cell *cell, Unit::Type unitType):
    Object(cell, Object::Unit), unitType(unitType)
{}


Unit::Type Unit::getUnitType() const{
    return unitType;
}


