#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector>
#include <string>
#include "Units/unit.h"
#include "observer.h"
#include "compositeunit.h"
#include "UnitsFactory/archersfactory.h"
#include "UnitsFactory/cavalryfactory.h"
#include "UnitsFactory/infantryfactory.h"
#include "Units/unit.h"

class GameField;

class Base : public Observer
{
public:
    void createUnit(std::string);
    void deleteUnit(Unit*);
    void printAll() const;
    void update(Subject* subject) override;

    friend class GameField;

private:
    Base(int, int, int, int, GameField*);
    int unitCount;
    const int maxCount;
    int health;
    const int x, y;
    CompositeUnit* units;
    GameField* field;
    const std::vector <std::string> unitsNames = {"Flatbow", "Longbow", "Dragoon", "Hussar", "Swordsman", "Spearman"};
};

#endif // BASE_H
