//
// Created by andrei on 04.04.2020.
//

#ifndef OOP_LAB2_GAME_H
#define OOP_LAB2_GAME_H

#include "../field/field.h"

class Game {
public:
    void addUnit(int x, int y, char type, int baseNum);

    void addNeutral(int x, int y, char type);

    void addBase(int x, int y);

    void moveUnit(int x1, int y1, int x2, int y2);

    void createField(int sizeX, int sizeY);

    void printField();

    pair<bool,bool> attack(Unit* unit1, Unit* unit2);

private:
    Field* field;
};


#endif //OOP_LAB2_GAME_H
