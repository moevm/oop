//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_FIELD_H
#define OOP_LAB1_FIELD_H

#include <iostream>
#include "../units/unit.h"
#include "../base/base.h"
#include "../neutral/neutral.h"
#include "../vector/vector.h"
#include "../vector/vector.cpp"
#include "../landscape/landscape.h"
#include "../cell/cell.h"

using namespace std;

class Field {
public:
    explicit Field(int sizeX = 1, int sizeY = 1);

    Field(Field& field);

    Field(Field&& field) noexcept;

    Field & operator=(Field& field);

    Field& operator=(Field&& field) noexcept;

    Cell* getCell(int x, int y);

    Base* getBase(int ind);

    void addBase(int x, int y);

    void printField();

private:
    unsigned int sizeX, sizeY;

    Vector<Vector<Cell*>> cells;
    Vector<Base*> bases;
};


#endif //OOP_LAB1_FIELD_H
