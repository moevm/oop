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
#include "Adapter.h"
#include "SnapShot.h"

class Cell;
class Unit;
class Base;
class Neutral;
class Adapter;
class SnapShot;

class Field{
    int gameMode;

    int X, Y;
    Cell** matrix;
    int objectsCounter;
    int maxObjectsOnField;
    Adapter* adapter;

public:

    Base* base1;
    Base* base2;
    Base* base3;

    Unit* unit1;
    Unit* unit2;

    Field(Adapter*);

    Field(int x, int y, Adapter*, int);

    ~Field();

    int getX() const;

    int getY() const;

    bool checkPoint(int x, int y) const;

    int getObjectCounter() const;

    bool addUnit(Unit* Object, int x, int y, std::string);

    void deleteUnit(Unit* Object);

    void moveUnit(Unit* Object, int x, int y);

    void print() const;

    Field(const Field& obj); // copy constructor

    Field(Field&& obj); // move constructor

    Field& operator= (const Field& obj);

    Base* setBase(int, int, int, int, int);

    void printLandscape() const;

    void printNeutrals() const;

    void attack(int, int, int);

    void deleteBase(Base*);

    Unit* findUnit(std::string&);

    Base* findBase(int);

    friend class FieldIterator;

    SnapShot* makeSnapShot(std::string);

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
