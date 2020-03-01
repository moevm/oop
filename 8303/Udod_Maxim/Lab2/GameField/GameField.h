//
// Created by shenk on 14.02.2020.
//

#ifndef UNTITLED13_GAMEFIELD_H
#define UNTITLED13_GAMEFIELD_H

#include "../Point.h"
#include "../Objects/GameObject.h"
#include "GameFieldIterator.h"
#include "FieldCell.h"

class Unit;

class GameField {

private:

    static GameField *gameField;

    FieldCell **field;

    int fieldHeight;
    int fieldWidth;

    GameField();
    explicit GameField(int fieldSize);
    GameField(int fieldHeight, int fieldWidth);
    GameField(const GameField &other) = delete;
    GameField(GameField &&other) = delete;
    ~GameField();

public:

    static void init( int fieldHeight, int fieldWidth);
    static GameField *getInstance();

    void deleteObject(int x, int y);
    void deleteObject(const Point &point);
    void deleteObject(GameObject *object);

    void addObject(GameObject *object, int x, int y);

    void moveObject(const Point &p1, const Point &p2);
    void moveObject(GameObject *object, const Point &p2);

    int getHeight() const;
    int getWidth() const;
    FieldCell *getCell(const Point &p) const;

    GameFieldIterator begin(){ return GameFieldIterator(Point(0, 0), field, fieldHeight, fieldWidth); }
    GameFieldIterator end(){ return GameFieldIterator(Point(0, fieldHeight), field, fieldHeight, fieldWidth); }

};
#endif //UNTITLED13_GAMEFIELD_H
