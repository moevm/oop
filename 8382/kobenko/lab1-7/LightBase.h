//
// Created by vlad on 02.06.2020.
//

#ifndef UNTITLED_LIGHTBASE_H
#define UNTITLED_LIGHTBASE_H
#include "LightArmy.h"
#include "Field.h"
#include <cstdlib>

class LightBase {
public:
    LightBase();
    int CreateUnits();
    int ControlUnits(Field&);
    LightArcher createLightArcher();
    LightInfantry createLightInfantry();
    LightCavalry createLightCavalry();
    int checkBase();
    void getDamage(int);
public:
    char type;
    int y;
    int x;
private:
    int health;
};


#endif //UNTITLED_LIGHTBASE_H
