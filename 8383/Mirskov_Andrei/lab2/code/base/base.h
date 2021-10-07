//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_BASE_H
#define OOP_LAB1_BASE_H

#include "../factory/factory.h"
#include "../vector/vector.h"

class Base {
public:
    explicit Base(int baseNum, int health = 50);

    Unit* createUnit(char type);

    void update(Unit*);

    int getNum();

    void takeDamage(int damage);

private:
    int health;
    int baseNum;
    const int maxUnit = 5;

    Vector<Unit*> onView;

};


#endif //OOP_LAB1_BASE_H
