#include "spineslandscape.h"


void SpinesLandscape::hurtUnit(Unit* unit)
{
    unit->toHurt(1);
}


bool SpinesLandscape::canMove(Unit* unit)
{
    Q_UNUSED(unit);

    return true;
}


Landscape* SpinesLandscape::clone()
{
    return new SpinesLandscape;
}


char SpinesLandscape::draw()
{
    return ',';
}
