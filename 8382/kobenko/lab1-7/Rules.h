//
// Created by vlad on 02.06.2020.
//

#ifndef UNTITLED_RULES_H
#define UNTITLED_RULES_H
#include "Field.h"
#include "DarkBase.h"
#include "DarkArmy.h"
#include "LightBase.h"
#include "LightArmy.h"

template<class T>
class Rules {
public:
    T base;
    bool maxUnits(Field &field);
    bool isBaseStillAlive();
    bool TooMuchTurns(int);
};


#endif //UNTITLED_RULES_H
