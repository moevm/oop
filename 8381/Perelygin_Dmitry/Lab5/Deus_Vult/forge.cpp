#include "forge.h"

void Forge::operator+= (Unit& unit)
{
    unit.set_attack(5);
}

