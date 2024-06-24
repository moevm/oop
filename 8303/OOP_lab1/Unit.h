
#ifndef OOP_LAB1_UNIT_H
#define OOP_LAB1_UNIT_H

#include "Armor.h"
#include "Weapon.h"
#include "Point.h"

class Unit {

    friend class GameField;

protected:

    Point position;

    Armor armor;
    Weapon weapon;
    int health;

    bool isOnField = false;

public:

    Unit(Unit *other);
    Unit() {}

    Point& getPosition() { return position; }

};

#endif //OOP_LAB1_UNIT_H
