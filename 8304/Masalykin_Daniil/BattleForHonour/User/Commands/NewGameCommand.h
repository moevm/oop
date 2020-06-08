#ifndef BATTLEFORHONOUR_NEWGAMECOMMAND_H
#define BATTLEFORHONOUR_NEWGAMECOMMAND_H


#include "Command.h"

class NewGameCommand: public Command {

public:

    explicit NewGameCommand(){}
    void execute(GameState &gameState) override{
        gameState.newGame();
    }

};

class NewGameCommandHandler: public CommandHandler {

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() == 1 && terminal[0] == "game";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){
            return std::unique_ptr<Command>(new NewGameCommand());
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }

};


#endif //BATTLEFORHONOUR_NEWGAMECOMMAND_H
