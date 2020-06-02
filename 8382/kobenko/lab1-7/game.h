//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H
#include "Field.h"
#include "DarkBase.h"
#include "LightBase.h"

class Game{
public:
    void InfiniteCycle(Field& field);
    int MovingUnits(char, int , int,  LightInfantry&, LightCavalry&, LightArcher&, DarkInfantry&, DarkCavalry&, DarkArcher&, Field&);
    int AttackingUnits(char, char,  LightInfantry&, LightCavalry&, LightArcher&, DarkInfantry&, DarkCavalry&, DarkArcher&, DarkBase&, LightBase&);
};

#endif //UNTITLED_GAME_H
