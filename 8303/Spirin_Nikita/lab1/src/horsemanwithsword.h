#ifndef HORSEMANWITHSWORD_H
#define HORSEMANWITHSWORD_H

#include "horseman.h"

class HorsemanWithSword : public Horseman
{
public:
    HorsemanWithSword(int health = 450, int damage = 40, int armor = 20, int speed = 7);
    char getID() const;
};

#endif // HORSEMANWITHSWORD_H
