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
    static int CreateUnits();
    static int ControlUnits(Field&);
    static DarkArcher createDarkArcher();
    static DarkInfantry createDarkInfantry();
    static DarkCavalry createDarkCavalry();
    int checkBase() const;
    void getDamage(int);
public:
    int x;
    int y;
    char type;
    int health;
};


#endif //UNTITLED_DARKBASE_H
