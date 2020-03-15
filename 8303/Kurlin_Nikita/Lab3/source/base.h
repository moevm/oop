#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector>
#include <string>
#include "Units/unit.h"
#include "compositeunit.h"
#include "UnitsFactory/archersfactory.h"
#include "UnitsFactory/cavalryfactory.h"
#include "UnitsFactory/infantryfactory.h"
#include "Units/unit.h"

class GameField;

class Base
{
public:
    Base(int, int, int, int, GameField*);
    Unit* createUnit(std::string);
    void deleteUnit(Subject*);
    void printAll();
    int getCapacityCount();
    Unit* getCurrUnit();
    int getX();
    int getY();
    bool getDamage(int);

    friend class BaseStatusCommand;

private:
    int unitCount;
    const int maxCount;
    int unitCurr;
    int health;
    const int x, y;
    CompositeUnit* units;
    GameField* field;
    const std::vector <std::string> unitsNames = {"Flatbow", "Longbow", "Dragoon", "Hussar", "Swordsman", "Spearman"};
};

#endif // BASE_H
