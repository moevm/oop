#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include <Landscapes/landscapeprotected.h>
#include "Units/unit.h"

//Proxy class for LandscapeProtected
class Landscape
{
public:
    LandscapeProtected realLandscape;

    virtual bool canStand(Unit* unit) = 0;
    virtual std::string getLandscapeType() = 0;
};

#endif // LANDSCAPE_H
