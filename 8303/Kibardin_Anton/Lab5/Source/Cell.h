//
// Created by anton on 16.02.2020.
//

#ifndef OOP_1_CELL_H
#define OOP_1_CELL_H

//#include "Unit.h"
#include "Base.h"

class Unit;
class Base;
class Landscape;
class Neutral;

class Cell {
public:
    Landscape* landscape;
    Base* base;
    Unit* unit;
    Neutral* neutral;

    Cell();

    Cell(const Cell& obj);

    Cell& operator=(const Cell& obj);

    void clearCell();

    void setCharacter(Unit* Object);

    void setLandscape(Landscape* landscape);

    void setBase(Base* base);

    void setNeutral(Neutral*);

    Unit* getCharacter() const;

    Landscape* getLandscape() const;

    Neutral* getNeutral() const;

    bool isAvailable(const Unit*) const;
};


#endif //OOP_1_CELL_H
