//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_DARKARMY_H
#define UNTITLED_DARKARMY_H

#include <iostream>
#include "Infantry.h"
#include "Cavalry.h"
#include "Archers.h"


class DarkArcher:public Archers {
public:
    int x;
    int y;
    char type;
    int health;
public:
    DarkArcher();
    int MoveUnits(int, int);
    int AttackUnits();
    void getDamage(int);
private:
    int attack;
    int armor;
};

class DarkInfantry:public Infantry {
public:
    int x;
    int y;
    char type;
    int health;
public:
    DarkInfantry();
    int MoveUnits(int, int) ;
    int AttackUnits();
    void getDamage(int);
private:
    int attack;
    int armor;
};

class DarkCavalry:public Cavalry {
public:
    int x;
    int y;
    char type;
    int health;
public:
    DarkCavalry();
    int MoveUnits(int, int) ;
    int AttackUnits() ;
    void getDamage(int);
private:
    int attack;
    int armor;
};


#endif //UNTITLED_DARKARMY_H
