#include "armory.h"

void Armory::operator+= (Unit& unit)
{
    unit.set_armor(3);
}
