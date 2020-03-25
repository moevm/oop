#include <iostream>
#include "GameFacade.h"
#include "Logs/Loggers/TerminalLogger.h"
#include "Logs/Formats/TimeFormat.h"

int main() {

    game::log.setLogger(new TerminalLogger());
    game::log.setLogFormat(new TimeFormat());

    GameFacade game(2, 3, 3);

    while (!game.isOver()){

        std::cout << game;
        game.nextTurn();

    }

    return 0;
}
