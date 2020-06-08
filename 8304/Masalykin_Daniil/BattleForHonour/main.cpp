#include <iostream>
#include "Game/GameFacade.h"
#include "Logs/FileLogger.h"
#include "Logs/CmdLogger.h"
#include "GameSettings/BigGame.h"
#include "GameSettings/MidGame.h"
#include "GameSettings/SmallGame.h"
#include "GameSettings/HillKing.h"

int main() {

    Log::log.setLogFormat(new CmdLogger());
    Log::log.setLogStrOutput(new LogString());

    auto game = GameFacade<SmallGame, 2>::single();

    while (!game.isOver()){
        std::cout << game;
        game.nextTurn();
    }

    return 0;
}