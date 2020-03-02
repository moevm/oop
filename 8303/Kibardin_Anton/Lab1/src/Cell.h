//
// Created by anton on 16.02.2020.
//

#ifndef OOP_1_CELL_H
#define OOP_1_CELL_H

#include "Unit.h"

class Unit;

class Cell {
    Unit* Object;
    public:
    Cell();
    Cell(const Cell& obj);
    Cell& operator=(const Cell& obj);
    void clearCell();
    void setCharacter(Unit* Object);
    Unit* getCharacter() const;
};


#endif //OOP_1_CELL_H
