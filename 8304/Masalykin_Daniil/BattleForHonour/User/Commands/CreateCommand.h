#ifndef BATTLEFORHONOUR_CREATECOMMAND_H
#define BATTLEFORHONOUR_CREATECOMMAND_H


#include "Command.h"
#include "CreateUnitCommand.h"
#include "CreateBaseCommand.h"

class CreateCommandHandler: public CommandHandler {

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() > 1 && terminal[0] == "create";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){
            terminal.erase(terminal.begin());

            auto handleUnit = new CreateUnitCommandHandler();
            auto handleBase = new CreateBaseCommandHandler();
            handleUnit->setNext(handleBase);

            return handleUnit->handle(terminal);
        }
        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }

};

#endif //BATTLEFORHONOUR_CREATECOMMAND_H
