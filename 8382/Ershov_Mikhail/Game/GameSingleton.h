#pragma once

#include "../Interfaces/Game.h"
#include "Rules/RuleWith.h"
#include "Rules/RuleWithout.h"
#include <string>

class GameSingleton {
public:
    void startGame();

private:
    //Game<Rules>* game = nullptr;
    Game<RuleWith>* gameWith = nullptr;
    Game<RuleWithout>* gameWithout = nullptr;
};
