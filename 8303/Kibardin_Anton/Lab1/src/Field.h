//
// Created by anton on 16.02.2020.
//

#ifndef OOP_1_FIELD_H
#define OOP_1_FIELD_H

#include "Cell.h"
#include "Unit.h"

class Cell;
class Unit;

class Field{
    int X, Y;
    Cell** matrix;
    int objectsCounter;
    int maxObjectsOnField;
public:
    Field();
    Field(int x, int y);
    ~Field();
    int getX() const;
    int getY() const;
    bool checkPoint(int x, int y) const;
    void swapCharacters(int x1, int y1, int x2, int y2);
    int getObjectCounter() const;
    void addObject(Unit* Object, int x, int y);
    void deleteObject(Unit* Object);
    void print() const;
    Field(const Field& obj); // copy constructor
    Field(Field&& obj); // move constructor
    Field& operator=(const Field& obj);
    Field& operator=(Field&& obj);
};


#endif //OOP_1_FIELD_H
