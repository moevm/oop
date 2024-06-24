#include "composit.h"

void Composit::add_unit(Unit* unit)
{
    arrUnits.push_back(unit);
}

void Composit::remove_unit(Unit *unit)
{
    std::vector<Unit*>::iterator iterator = arrUnits.begin();
    while(iterator != arrUnits.end())
    {
        if(*iterator == unit)
        {
            arrUnits.erase(iterator);
            break;
        }
        iterator++;
    }
}
