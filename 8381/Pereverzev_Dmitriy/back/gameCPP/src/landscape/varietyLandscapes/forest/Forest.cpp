#include "Forest.hpp"

unsigned int Forest::getLandscapeType()
{
    return FOREST;
}
bool Forest::checkAccessMove(unsigned int objectType)
{
    return true;
}
bool Forest::checkAccessInteraction(unsigned int objectType)
{
    return true;
}