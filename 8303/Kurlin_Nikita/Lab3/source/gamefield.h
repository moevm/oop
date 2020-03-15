#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <iostream>
#include <Units/unit.h>
#include "Landscapes/landscape.h"
#include "Landscapes/forests.h"
#include "Landscapes/mountains.h"
#include "Landscapes/rivers.h"
#include "base.h"
#include "observer.h"
#include "NeutralObject/neutralobject.h"
#include "NeutralObject/poison.h"
#include "NeutralObject/weapon.h"
#include "NeutralObject/armor.h"
#include "NeutralObject/medicine.h"

class Mediator;

struct Point
{
    int x, y;
    Unit* unit;
    Landscape* landscape;
    Base* base;
    NeutralObject* nObject;
};

class GameField : public Observer
{
public:
    GameField(int, int, int);
    GameField(const GameField &);
    GameField(GameField &&);
    bool canStand(Base*, std::string, int, int);
    bool createUnit(std::string, Base*, Mediator*);
    void deleteUnit(Subject*);
    void moveUnitLeft(Unit*, Base*);
    void moveUnitRight(Unit*, Base*);
    void moveUnitUp(Unit*, Base*);
    void moveUnitDown(Unit*, Base*);
    Point* findUnit(Unit*);
    void printAll() const;
    Base* setBase(int, int, int, int);
    void setUnit(Unit*, int, int, Base*);
    void update(Subject* subject) override;

    friend class Iterator;
    friend class Mediator;
    Base* base1;
    Base* base2;

private:
    const int x;
    const int y;
    int unitCount;
    const int maxCount;
    Point*** pointsMap;     //Двумерный массив указателей на ячейки Point на поле
    const std::vector <std::string> unitsNames = {"Flatbow", "Longbow", "Dragoon", "Hussar", "Swordsman", "Spearman"};

    void moveUnit(Unit*, int, int, Base*);
};

#endif // GAMEFIELD_H
