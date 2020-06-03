#include "LandscapeProxy.hpp"
LandscapeProxy::LandscapeProxy()
{
    landscape = nullptr;
}

LandscapeProxy::LandscapeProxy(unsigned int landscapeType)
{
    if (landscapeType == FOREST)
        landscape = new Forest;
    if (landscapeType == MOUNTAIN)
        landscape = new Mountain;
    if (landscapeType == PLAIN)
        landscape = new Plain;
    if (landscapeType == SWAMP)
        landscape = new Swamp;
}

LandscapeProxy ::~LandscapeProxy()
{
    delete landscape;
}

unsigned int LandscapeProxy::getLandscapeType()
{
    return landscape->getLandscapeType();
    
}
bool LandscapeProxy::checkAccessMove(unsigned int objectType)
{

    unsigned int landscapeType = landscape->getLandscapeType();
    if (!landscape->checkAccessMove(0))
        return false;
    if (objectType % 2)
        if (landscapeType == FOREST)
            return false;
    if (!(objectType % 2))
        if (landscapeType == SWAMP)
            return false;

    if (objectType == ARCH_DPS || objectType == ARCH_TANK)
        if (landscapeType == SWAMP)
            return false;
    if (objectType == CAV_DPS || objectType == CAV_TANK)
        if (landscapeType == FOREST)
            return false;

    return true;
}

bool LandscapeProxy::checkAccessInteraction(unsigned int objectType)
{
    unsigned int landscapeType = landscape->getLandscapeType();
    if (!landscape->checkAccessMove(0))
        return false;

    if (objectType == ARCH_DPS || objectType == ARCH_TANK)
        if (landscapeType == FOREST)
            return false;
    if (objectType == INF_DPS || objectType == INF_TANK || objectType == CAV_DPS || objectType == CAV_TANK)
        if (landscapeType == SWAMP)
            return false;
    return true;
}