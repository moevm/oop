//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_BASE_H
#define OOP_LAB1_BASE_H


#include "../units/unit.h"
#include "../vector/vector.h"
#include "../factory/factory.h"

class Base {
public:
    Base(int x, int y, int health = 50);

    void addUnit(int x, int y, char type);

    void removeUnit(int x, int y);

    void moveUnit(int x1, int y1, int x2, int y2);

    void takeItem(int x1, int y1, Neutral* neutral);

    bool isUnit(int x, int y);

    Unit* getUnit(int x, int y);

    void takeDamage(int damage);

private:
    int x, y;
    int health;
    const int maxUnit = 10;

    Vector<Unit*> units;

};


#endif //OOP_LAB1_BASE_H
