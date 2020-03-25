#ifndef BASE_H
#define BASE_H

#include "compositeUnit.h"
#include <Units/Factory/creaturesArmy.h>
#include <Units/Factory/humanityArmy.h>

class Base
{
public:
    Base(int, int, int, int, int);

    int getBaseNumb() const;
    int getX() const;
    int getY() const;
    int getUnitCount() const;
    int getMaxCount() const;
    int getHealth() const;

    Unit* createUnit(std::string);
    void addUnit(Unit* u);
    void deleteUnit(Subject*);
    Unit* getCurrUnit();
    bool getDamage(int numb);

private:
    int baseNumb;
    int unitCount;
    const int maxCount;
    int health;
    const int x, y;
    CompositeUnit* units;
    int unitCurr;
};

#endif // BASE_H
