#ifndef SPEARMAN_H
#define SPEARMAN_H

#include "unit.h"
#include "infantry.h"

class Spearman : public Infantry
{
public:
    Spearman(int health = 280, int damage = 35, int armor = 15, int speed = 5);
    char getID() const;
};

#endif // SPEARMAN_H
