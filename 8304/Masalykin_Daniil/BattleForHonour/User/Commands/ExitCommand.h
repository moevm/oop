#ifndef BATTLEFORHONOUR_EXITCOMMAND_H
#define BATTLEFORHONOUR_EXITCOMMAND_H

#include "Command.h"

class ExitCommand: public Command{

    void execute(GameState &gameState) override{
        exit(0);
    }

};

class ExitCommandHandler: public CommandHandler{

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() == 1 && terminal[0] == "exit";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){
            terminal.erase(terminal.begin());
            return std::unique_ptr<Command>(new ExitCommand());
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();

    }

};


#endif //BATTLEFORHONOUR_EXITCOMMAND_H
