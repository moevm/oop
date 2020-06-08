#ifndef BATTLEFORHONOUR_ATTACKCOMMAND_H
#define BATTLEFORHONOUR_ATTACKCOMMAND_H


#include "Command.h"
#include "AttackUnitCommand.h"

class AttackCommandHandler: public CommandHandler {

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() > 1 && terminal[0] == "attack";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)) {
            terminal.erase(terminal.begin());
            auto handleAttack = new AttackUnitCommandHandler();
            return handleAttack->handle(terminal);
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }
};


#endif //BATTLEFORHONOUR_ATTACKCOMMAND_H
