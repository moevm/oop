#ifndef CROSSBOWMAN_H
#define CROSSBOWMAN_H

#include "unit.h"
#include "shooter.h"

class Crossbowman : public Shooter
{
public:
    Crossbowman(int health = 200, int damage = 60, int armor = 8, int speed = 4, int firingRange = 8);
    char getID() const;
};

#endif // CROSSBOWMAN_H
