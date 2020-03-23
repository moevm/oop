//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_FIELD_H
#define OOP_LAB1_FIELD_H

#include <iostream>
#include "../units/unit.h"
#include "../vector/vector.h"
#include "../vector/vector.cpp"
#include "../neutral/neutral.h"
#include "../landscape/landscape.h"
#include "../landscape/ground.h"
#include "../landscape/liquid.h"
#include "../landscape/wall.h"
#include "../base/base.h"

using namespace std;

class Field {
public:
    explicit Field(int sizeX = 1, int sizeY = 1, int base1x = 0, int base1y = 0, int base2x = 1, int base2y = 1);

    Field(Field& field);

    Field(Field&& field) noexcept;

    Field & operator=(Field& field);

    Field& operator=(Field&& field) noexcept;

    void addUnit(int x, int y, char type, int playerNum);

    void removeUnit(int x, int y);

    void addNeutral(int x, int y, char type);

    void removeNeutral(int x, int y);

    void moveUnit(int x1, int y1, int x2, int y2, int playerNum);

    void takeItem(int x1, int y1, int x2, int y2, int playerNum);

    void attack(int x1, int y1, int x2, int y2, int playerNum);

    bool isNeutral(int x, int y);

    bool isUnit(int x, int y);

    void printField();

private:
    unsigned int sizeX, sizeY;

    Base* base1;
    Base* base2;

    Vector<Neutral*> neutrals;
    Vector<Vector<Landscape*>> cells;

    Vector<Vector<char>> picture;
};


#endif //OOP_LAB1_FIELD_H
