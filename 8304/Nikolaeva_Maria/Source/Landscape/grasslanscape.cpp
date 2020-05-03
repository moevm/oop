#include "grasslanscape.h"


void GrassLanscape::hurtUnit(Unit* unit)
{
    Q_UNUSED(unit);
}


bool GrassLanscape::canMove(Unit* unit)
{
    Q_UNUSED(unit);

    return true;
}


Landscape* GrassLanscape::clone()
{
    return new GrassLanscape;
}

char GrassLanscape::draw()
{
    return '.';
}
