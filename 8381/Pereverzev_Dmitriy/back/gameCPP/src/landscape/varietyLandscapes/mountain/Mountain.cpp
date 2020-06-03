#include "Mountain.hpp"

unsigned int Mountain::getLandscapeType()
{
    return MOUNTAIN;
}
bool Mountain::checkAccessMove(unsigned int objectType)
{
    return false;
}

bool Mountain::checkAccessInteraction(unsigned int objectType)
{
    return false;
}