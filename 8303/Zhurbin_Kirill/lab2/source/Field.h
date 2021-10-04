#ifndef OOP1_FIELD_H
#define OOP1_FIELD_H

#include <iostream>
#include "Unit.h"
#include "Landscape.h"
#include "Wall.h"
#include "Water.h"
#include "Ground.h"
#include "Base.h"
#include "NeutralObject.h"

struct Cell{
    int x, y;
    Unit* unit;
    Landscape* landscape;
    Base* base;
    NeutralObject* neutralObject;
};

class Field{
private:
    const int lenghtX, lengthY;
    const int maxCountObject;
    int countUnit;
    Cell ***mapCell;

public:
    friend class Iterator;

    Field(int x, int y, int maxCountObject);

    Field(const Field &field);

    Field(Field &&field);

    bool addUnit(Unit *unit, int, int);

    void removeUnit(Unit *unit);

    void printAll();

    void moveUnit(Unit *unit, int x, int y);

    void moveUnitLeft(Unit *unit);

    void moveUnitUp(Unit *unit);

    void moveUnitRight(Unit *unit);

    void moveUnitDown(Unit *unit);

    Cell *findUnit(Unit *unit);

    void addLandscape();

    void printLandscape();

    Base* createBase(int BaseX, int BaseY, int maxCountUnit, int health);

    void addNeutral(int NeutralX, int NeutralY, char name);

    void printNeutral();
};
#endif //OOP1_FIELD_H
