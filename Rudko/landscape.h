#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "unit.h"

class Landscape
{
public:
    virtual bool isMoved(Unit* ) = 0;
    virtual bool isDamage(Unit* ) = 0;
};

#endif // LANDSCAPE_H
