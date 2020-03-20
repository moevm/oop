#ifndef INFANTRY_H
#define INFANTRY_H

#include "unit.h"

class Infantry : public Unit
{
public:
    Infantry(int health, int damage, int armor, int speed);
};

#endif // INFANTRY_H
