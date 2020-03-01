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

struct Point
{
    int x, y;
    Unit* unit;
    Landscape* landscape;
    Base* base;
    NeutralObject* nObject;
};

class GameField
{
public:
    GameField(int, int, int);
    GameField(const GameField &);
    GameField(GameField &&);
    bool addUnit(Unit*, int, int);
    void deleteUnit(Unit*);
    void moveUnitLeft(Unit*);
    void moveUnitRight(Unit*);
    void moveUnitUp(Unit*);
    void moveUnitDown(Unit*);
    void printAll() const;
    Base* setBase(int, int, int, int);

    friend class Iterator;

private:
    const int x;
    const int y;
    int unitCount;
    const int maxCount;
    Point*** pointsMap;	//Двумерный массив указателей на ячейки Point на поле

    Point* findUnit(Unit*);
    void moveUnit(Unit*, int, int);
};

#endif // GAMEFIELD_H
