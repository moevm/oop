//
// Created by shenk on 14.02.2020.
//

#ifndef UNTITLED13_GAMEFIELD_H
#define UNTITLED13_GAMEFIELD_H

#include "Point.h"
#include "Units/Unit.h"
#include "GameFieldIterator.h"

class Unit;

class GameField {

    friend class Unit;

private:

    Unit ***field;

    int fieldHeight;
    int fieldWidth;

    int maxObjectsCount = 3;

public:

    GameField(int fieldSize);
    GameField(int fieldHeight, int fieldWidth);
    GameField(GameField &other);
    GameField(GameField &&other);

    void deleteObject(int x, int y);
    void deleteObject(Point &point);
    void deleteObject(Unit *object);

    void addObject(Unit *object, int x, int y);

    void moveObject(Point &p1, Point &p2);
    void moveObject(Unit *object, Point &p2);

    Unit ***getField(){ return field; }

    int getHeight();
    int getWidth();
    Unit *getObject(Point &p);

    GameFieldIterator begin(){ return GameFieldIterator(Point(0, 0), field, fieldHeight, fieldWidth); }
    GameFieldIterator end(){ return GameFieldIterator(Point(0, fieldHeight), field, fieldHeight, fieldWidth); }

};

#endif //UNTITLED13_GAMEFIELD_H
