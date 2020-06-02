#include "unit.h"
#include <iostream>
#ifndef BASE_H
#define BASE_H

using namespace std;

/* отдел базы */

class Base{
public:
    int hp;
    int x, y;
    int countOfUnits = 0;
    int gold = 500;
    char sym = 'B';
    Unit* createUnit(int code, ArmyFactory& factory);
};


#endif // BASE_H
