#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "unit.h"
#include "infantry.h"

class Swordsman : public Infantry
{

public:
    Swordsman(int health = 300, int damage = 40, int armor = 20, int speed = 5);
    char getID() const;
};

#endif // SWORDSMAN_H
