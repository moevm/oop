#ifndef HORSEMANWITHSPEAR_H
#define HORSEMANWITHSPEAR_H

#include "horseman.h"

class HorsemanWithSpear : public Horseman
{
public:
    HorsemanWithSpear(int health = 400, int damage = 35, int armor = 15, int speed = 8);
    char getID() const;
};

#endif // HORSEMANWITHSPEAR_H
