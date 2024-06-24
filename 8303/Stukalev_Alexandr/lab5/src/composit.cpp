#include "composit.h"
#include "adapter.h"
#include <iostream>


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

void Composit::print_units()
{
    std::cout << '\n';
    for(size_t i = 0; i < arrUnits.size(); i++)
    {
        std::string str = Adapter::adaptUnitPrint(arrUnits[i]);
        std::cout << str;
    }
}
