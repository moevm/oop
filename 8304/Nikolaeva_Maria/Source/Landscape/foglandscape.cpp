#include "foglandscape.h"


void FogLandscape::hurtUnit(Unit* unit)
{
    Q_UNUSED(unit);
}


bool FogLandscape::canMove(Unit* unit)
{
    Q_UNUSED(unit);

    return false;
}

Landscape* FogLandscape::clone()
{
    return new FogLandscape;
}


char FogLandscape::draw()
{
    return '~';
}
