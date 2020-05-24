#pragma once

#include "Game.h"
#include "RuleWith.h"
#include "RuleWithout.h"
#include <string>

class GameSingleton {
public:
    void startGame();

private:
    //Game<Rules>* game = nullptr;
    Game<RuleWith>* gameWith = nullptr;
    Game<RuleWithout>* gameWithout = nullptr;
};
