//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <vector>
#include "../../Units/Unit.h"
#include "../Factories/UnitFactories.h"

class Field;

class Base {
    const int xPosition;
    const int yPosition;
    int healthBase;
    const int maxCountUnitsOnBase;
    const int maxCountUnitsInGame;
    int countUnitsOnBase;
    int countUnitsInGame;
    int money;
    Unit **units;
    UnitFactory *factory;
    Field *field;
public:
    explicit Base(Unit **units, int x,int y, int maxCountUnitsInGame,Field *field);
    ~Base();
    void addSwordsmen(int x,int y);
    void addSpearmen(int x,int y);
    void addArcher(int x,int y);
    void addMagician(int x,int y);
    void addKnight(int x,int y);
    void addKing(int x,int y);

    void handleEvent(const Unit& unit);
    int getCountUnitsInGame() const;

    std::vector<int> vectorDeleteUnits;

    const int getXPosition() const;

    const int getYPosition() const;

    void addUnit(int x,int y,Unit *unit);

    int getHealthBase() const;

    int getCountUnitsOnBase() const;

    int getMoney() const;
};


#endif //GAME_BASE_H
