#ifndef ARCHER_H
#define ARCHER_H

#include "unit.h"
#include "shooter.h"

class Archer : public Shooter
{
public:
    Archer(int health = 180, int damage = 40, int armor = 6, int speed = 4, int firingRange = 12);
    char getID() const;
};

#endif // ARCHER_H
