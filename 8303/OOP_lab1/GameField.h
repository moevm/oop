#ifndef OOP_LAB1_GAMEFIELD_H
#define OOP_LAB1_GAMEFIELD_H

#include "Point.h"
#include "Unit.h"
#include "GameFieldIterator.h"

class Unit;

class GameField {

    friend class Unit;

private:

    Unit ***field;

    int fieldHeight;
    int fieldWidth;
    int objectsCount;
    int maxObjectsCount = 3;

public:

    explicit GameField(int fieldSize);
    GameField(int fieldHeight, int fieldWidth);
    GameField(const GameField &other);
    GameField(GameField &&other);
    ~GameField();

    void deleteObject(int x, int y);
    void deleteObject(const Point &point);
    void deleteObject(Unit *object);

    void addObject(Unit *object, int x, int y);

    void moveObject(const Point &p1,const Point &p2);
    void moveObject(Unit *object, const Point &p2);

    Unit ***getField(){ return field; }

    int getHeight() const;
    int getWidth() const;
    Unit *getObject(const Point &p) const;

    GameFieldIterator begin(){ return GameFieldIterator(Point(0, 0), field, fieldHeight, fieldWidth); }
    GameFieldIterator end(){ return GameFieldIterator(Point(0, fieldHeight), field, fieldHeight, fieldWidth); }

};

#endif //OOP_LAB1_GAMEFIELD_H