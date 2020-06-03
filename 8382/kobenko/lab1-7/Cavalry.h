//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_CAVALRY_H
#define UNTITLED_CAVALRY_H
#include "Units.h"

class Cavalry:Units {
public:
    Cavalry() = default;
    virtual int MoveUnits(int , int ) = 0;
    virtual int AttackUnits(char** , char ) = 0;
    virtual void getDamage(int) =0;

public:
    char type;
    int health;
    int y;
    int x;
private:
    int attack;
    int armor;
};


#endif //UNTITLED_CAVALRY_H
