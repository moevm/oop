//
// Created by kholk on 14.04.2020.
//

#ifndef MYLITTLEGAME_GAME_H
#define MYLITTLEGAME_GAME_H

#endif //MYLITTLEGAME_GAME_H

#include "Field.h"

struct Game{
    struct selectedType{
        Point pos;
        bool isBase;
    };

    Game(int s, int l);
    void addBase();
    void select(Point const& a);
    void addUnit(Point const& a, char Name);
    void Attack(Point const& a);
    void moveUp();
    void moveLeft();
    void moveRight();
    void moveDown();
    void show();
private:
    Field field;
    selectedType selected;
};