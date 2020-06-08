//
// Created by therealyou on 01.06.2020.
//

#ifndef LAB1_SNAPSHOT_H
#define LAB1_SNAPSHOT_H


#include "Exception.h"
#include "Base.h"

class GameField;
class Base;
class Adapter;


class SnapShot {
    int gameMode;

    GameField *gameField;
    int height, width;
    Adapter *adapter;
    int playersNumber;

    Base *base1;
    Base *base2;
    Base *base3;

    Unit *unit1;
    Unit *unit2;
    Unit *unit3;

    std::ofstream *outStream;
    std::ifstream *inStream;
public:
    SnapShot(GameField *, Base *, Base *, Base *, Unit *, Unit *, Unit *, Adapter *, int);

    SnapShot(GameField *tmp);

    ~SnapShot();

    void save();

    void load();
};


#endif //LAB1_SNAPSHOT_H
