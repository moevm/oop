#ifndef BATTLEFORHONOUR_SKIPCOMMAND_H
#define BATTLEFORHONOUR_SKIPCOMMAND_H

#include "Command.h"

class SkipCommand: public Command{

    void execute(GameState &gameState) override{
        Log::log << "[#User] " << gameState.getNowPlayerIndex() << " skiped turn" << Log::logend;
    }

};

class SkipCommandHandler: public CommandHandler {

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() == 1 && terminal[0] == "skip";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){
            terminal.erase(terminal.begin());
            return std::unique_ptr<Command>(new SkipCommand());
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }

};

#endif //BATTLEFORHONOUR_SKIPCOMMAND_H
