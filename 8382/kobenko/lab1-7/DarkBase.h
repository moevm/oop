//
// Created by vlad on 02.06.2020.
//

#ifndef UNTITLED_DARKBASE_H
#define UNTITLED_DARKBASE_H
#include "DarkArmy.h"
#include "Field.h"
#include <cstdlib>

class DarkBase {
public:
    DarkBase();
    int CreateUnits();
    int ControlUnits(Field&);
    DarkArcher createDarkArcher();
    DarkInfantry createDarkInfantry();
    DarkCavalry createDarkCavalry();
    int checkBase();
    void getDamage(int);
public:
    int x;
    int y;
    char type;
private:
    int health;
};


#endif //UNTITLED_DARKBASE_H
