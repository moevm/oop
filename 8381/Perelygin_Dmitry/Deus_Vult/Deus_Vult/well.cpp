#include "well.h"


void Well::operator+= (Unit& unit)
{
    unit.set_hp(-5);
}
