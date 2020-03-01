#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <cstring>

#include "GameField/cellofgamefield.h"


class GameField
{
public:
    GameField(size_t height, size_t width);
    ~GameField();

    bool addUnit(Unit* unit);
    void deleteUnit(Unit* unit);
    CellOfGameField* getCell(int x, int y);
    int getWidth();
    int getHeight();
    size_t getNumberOfUnits();

    GameField* clone();

protected:
    size_t height;
    size_t width;
    size_t numberOfUnits;

    CellOfGameField** field;
};

#endif // GAMEFIELD_H
