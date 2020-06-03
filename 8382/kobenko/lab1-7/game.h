//
// Created by vlad on 01.06.2020.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H
#include "Field.h"
#include "DarkBase.h"
#include "LightBase.h"
#include "templates.cpp"

class Game{
public:
    void InfiniteCycle(Field& field);
    static int MovingUnits(Field&);
    static int AttackingUnits(Field&);
    int checkRules(Field& );
    void init(Field&);
};

#endif //UNTITLED_GAME_H
