#include "proxylandscape.h"


ProxyLandscape::ProxyLandscape()
{
    this->landscape = new GrassLanscape;
}


ProxyLandscape::ProxyLandscape(Landscape* landscape)
{
    this->landscape = landscape;
}


void ProxyLandscape::hurtUnit(Unit* unit)
{
    if (unit && !unit->isFlying()) {
        this->landscape->hurtUnit(unit);
    }
}


bool ProxyLandscape::canMove(Unit* unit)
{
    if (unit && unit->isFlying()) {
        return this->landscape->canMove(unit);
    }

    return true;
}


Landscape* ProxyLandscape::clone()
{
   return new ProxyLandscape(this->landscape->clone());
}


char ProxyLandscape::draw()
{
    return landscape->draw();
}
