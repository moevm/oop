#ifndef FACADEMEDIATOR_H
#define FACADEMEDIATOR_H

#include "Game/IFacadeMediator.h"
#include "GUI/command.h"

class FacadeMediator : public IFacadeMediator
{
public:
    FacadeMediator(std::shared_ptr<UIFacade> facade_, std::shared_ptr<Command> command_) :
        facade(std::move(facade_)), command(std::move(command_)) { }
    void sendString(Request request, std::string answer) override
    {
        facade->receiveStrAnswer(request, answer);
    }
private:
    std::shared_ptr<UIFacade> facade;
    std::shared_ptr<Command> command;
};

#endif // FACADEMEDIATOR_H
