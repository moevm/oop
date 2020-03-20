#ifndef SHOOTER_H
#define SHOOTER_H

#include "unit.h"

class Shooter : public Unit
{
    int firingRange;
public:
    Shooter(int health, int damage, int armor, int speed, char typeOfAttack = 's');
};

#endif // SHOOTER_H
