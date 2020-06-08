//
// Created by therealyou on 11.02.2020.
//

#ifndef LAB1_GAMEFIELD_H
#define LAB1_GAMEFIELD_H

#define DEFAULT_X 4
#define DEFAULT_Y 5
#define DEFAULT_VALUE '-'

#include <iostream>
#include "Units/Unit.h"
#include "SnapShot.h"
#include "Adapter.h"
#include "Base.h"
#include "Landscapes/Landscape.h"
#include "Landscapes/Desert.h"
#include "Landscapes/Mountain.h"
#include "Landscapes/Wood.h"
#include "NeutralObjetcs/Object.h"
#include "NeutralObjetcs/Armor.h"
#include "NeutralObjetcs/Medicine.h"
#include "NeutralObjetcs/Weapon.h"
#include "NeutralObjetcs/Poison.h"
#include "Landscapes/LandscapeProxy.h"

class Base;
class SnapShot;
class Adapter;

struct Cell {
    Unit *unit = nullptr;
    LandscapeProxy *landscape = new LandscapeProxy(new Desert());
    Object *neutralObject = nullptr;
    Base *base = nullptr;
    char valueAsChar = DEFAULT_VALUE;
    char charLandscape = 'D';
    char charNeutralObject = DEFAULT_VALUE;
};

class Unit;

class GameField : public Observer {
private:
    int gameMode;
    int width;
    int height;
    Cell **matrix;
    GameField *gameField;
    Adapter *adapter;

    int maxCountUnits;

    int countUnits = 0;

    void setMatrix();

    void setMatrix(Cell **matrix);

    bool canAdd(int x, int y);

public:
    Base *base1;
    Base *base2;
    Base *base3;

    Unit *unit1;
    Unit *unit2;
    Unit *unit3;

    int addUnit(Unit *unit, int x, int y);

    bool isCorrect(int x, int y);

    void attack(int x, int y, int attack);

    int getWidth() const;

    int getHeight() const;

    GameField(Adapter *);

    GameField(int x, int y, Adapter *adapter, int mode);

    GameField(const GameField &gameField);

    GameField(GameField &&gameField);

    GameField &operator=(const GameField &gameField);

    void printField() const;

    void printFieldLandscape() const;

    void printFieldNeutralObject() const;

    int createLandscape(Landscapes landscape, int x, int y);

    Object *createNeutralObject(ObjectsType type, int x, int y, int buffValue);

    Base *createBase(int x, int y, int baseNumber, int maxCountUnits = 3, int health = 100);

    Base *findBase(int baseId);

    void deleteBase(Base *base);

    Unit *findUnit(int unitId);

    void deleteUnit(int x, int y);

    void moveUnit(Unit *unit, int dx, int dy);

    void update(SubjectObserve *subjectObserve);

    SnapShot* makeSnapShot(const std::string&);

    class GameFieldIterator : public std::iterator<std::input_iterator_tag, Cell> {

    public:
        GameFieldIterator(const GameFieldIterator &it);

        bool operator!=(GameFieldIterator const &other) const;

        bool operator==(GameFieldIterator const &other) const; //need for BOOST_FOREACH
        typename GameFieldIterator::reference operator*() const;

        GameFieldIterator &operator++();

        GameFieldIterator(int height, int width, Cell **field, const int fieldHeight, const int fieldWidth);

    private:

        int x = 0, y = 0;
        Cell **field;
        Cell p;
        const int fieldHeight;
        const int fieldWidth;

    };

    GameFieldIterator begin();

    GameFieldIterator end();
};


#endif //LAB1_GAMEFIELD_H
