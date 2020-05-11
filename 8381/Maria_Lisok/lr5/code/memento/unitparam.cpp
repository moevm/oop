#include "unitparam.h"
UnitParam::UnitParam(string name, int baseNumber, Attributes *attributes):name(name), baseNumber(baseNumber), attributes(attributes)
{}
string UnitParam::getName() const
{
    return name;
}
int UnitParam::getBaseNumber() const
{
    return baseNumber;
}

Attributes *UnitParam::getAttributes() const
{
    return attributes;
}
