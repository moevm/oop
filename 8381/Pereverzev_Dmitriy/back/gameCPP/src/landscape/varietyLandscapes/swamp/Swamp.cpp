#include "Swamp.hpp"

unsigned int Swamp::getLandscapeType()
{
    return SWAMP;
}
bool Swamp::checkAccessMove(unsigned int objectType)
{
    return true;
}

bool Swamp::checkAccessInteraction(unsigned int objectType)
{
    return true;
}