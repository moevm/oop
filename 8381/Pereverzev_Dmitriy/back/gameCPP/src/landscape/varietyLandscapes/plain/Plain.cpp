#include "Plain.hpp"

unsigned int Plain::getLandscapeType()
{
    return PLAIN;
}
bool Plain::checkAccessMove(unsigned int objectType)
{
    return true;
}

bool Plain::checkAccessInteraction(unsigned int objectType)
{
    return true;
}