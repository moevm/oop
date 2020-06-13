//
// Created by anton on 16.02.2020.
//

#ifndef OOP_1_FIELD_H
#define OOP_1_FIELD_H

#include "Cell.h"
#include "Units/Unit.h"
#include "Base.h"
#include "Landscape.h"
#include "Neutral.h"
#include <iterator>

class Cell;
class Unit;
class Base;
class Neutral;

class Field{
    const int X, Y;
    Cell** matrix;
    int objectsCounter;
    const int maxObjectsOnField;

public:
    Field();

    Field(int x, int y);

    ~Field();

    int getX() const;

    int getY() const;

    bool checkPoint(int x, int y) const;

    void swapCharacters(int x1, int y1, int x2, int y2);

    int getObjectCounter() const;

    bool addUnit(Unit* Object, int x, int y);

    void deleteUnit(Unit* Object);

    void moveUnit(Unit* Object, int x, int y);

    void print() const;

    Field(const Field& obj); // copy constructor

    Field(Field&& obj); // move constructor

    Base* setBase(int, int, int);

    void printLandscape() const;

    void printNeutrals() const;


    friend class FieldIterator;
};

class FieldIterator final: public std::iterator<std::input_iterator_tag, Cell>{
    Field* fieldPtr;
    Cell* tmpCell;
    int x,y;

public:
    FieldIterator(Field* ptr);

    bool operator==(const FieldIterator& other) const;

    bool operator!=(const FieldIterator& other) const;

    Cell*& operator*();

    Cell*& operator++(int);

};


#endif //OOP_1_FIELD_H
