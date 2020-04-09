//
// Created by Alex on 22.03.2020.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H


#include "../OtherClasses/Base/Base.h"
#include "../OtherClasses/Field/Field.h"

class Game {
public:
    Game();

    ~Game();

private:
    Base *base;
    Field *field;
    Unit **units;
public:
    void getInformationAboutEnvironment(int *array, int x, int y);

    void updateUnitPosition(int lastX, int lastY, int newX, int newY);

    void addSwordsmen(int x, int y);

    void addSpearmen(int x, int y);

    void addArcher(int x, int y);

    void addMagician(int x, int y);

    void addKing(int x, int y);

    void addKnight(int x, int y);

    bool attackUnit(int xPositionUnit1, int yPositionUnit1,int xPositionUnit2, int yPositionUnit2);

    int getInformationAboutMoney();
    int getInformationAboutBaseHealth();
};


#endif //GAME_GAME_H
