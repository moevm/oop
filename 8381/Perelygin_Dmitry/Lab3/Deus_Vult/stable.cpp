#include "stable.h"

void Stable::operator+= (Unit& unit)
{
    unit.set_hp(-5);
}
