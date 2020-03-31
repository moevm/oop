#ifndef OOP1_SNAPSHOTFIELD_H
#define OOP1_SNAPSHOTFIELD_H

#include <memory>
#include <fstream>
#include <sstream>

#include "Field/point2d.h"


class Game;


struct UnitSnapshot
{
    char unit;
    double healthPoints;
    Point2D pos;
};


class Snapshot
{
public:
    static void save(const Game& game);

    static void load(Game& game);
};

#endif //OOP1_SNAPSHOTFIELD_H
