//
// Created by user on 03.05.2020.
//

#ifndef OOP_1_SNAPSHOT_H
#define OOP_1_SNAPSHOT_H


#include "Cell.h"
#include "Exception.h"
#include "Fabric.h"
class Cell;
class Field;
class Adapter;


class SnapShot {
    int gameMode;

    Field* field;
    int X, Y;
    Adapter* adapter;

    Base* base1;
    Base* base2;
    Base* base3;

    Unit* unit1;
    Unit* unit2;

    std::ofstream* outStream;
    std::ifstream* inStream;
public:
    SnapShot(Field* , Base*, Base*, Base*, Unit*, Unit*, Adapter*, int);

    SnapShot(Field* tmp);

    ~SnapShot();

    void save();

    void load();
};


#endif //OOP_1_SNAPSHOT_H
