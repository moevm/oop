#ifndef HORSEMAN_H
#define HORSEMAN_H

#include "unit.h"

class Horseman : public Unit
{
public:
    Horseman(int health, int damage, int armor, int speed);
};

#endif // HORSEMAN_H
