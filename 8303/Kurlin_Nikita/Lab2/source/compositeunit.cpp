#include "compositeunit.h"

CompositeUnit::CompositeUnit()
{

}

void CompositeUnit::addUnit(Unit *unit)
{
        unitsMas.push_back(unit);
}

void CompositeUnit::deleteUnit(Unit *unit)
{
    for(std::vector<Unit*>::iterator iter = unitsMas.begin(); iter != unitsMas.end(); iter++){
        if (*iter == unit){
            unitsMas.erase(iter);
            break;
        }
    }
}

void CompositeUnit::printAll()
{
    for(std::vector<Unit*>::iterator iter = unitsMas.begin(); iter != unitsMas.end(); iter++){
        std::cout << (*iter)->armyType << std::endl;
        //std::cout << (*iter)->attributes->health << std::endl;
    }
}
