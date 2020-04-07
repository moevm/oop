#ifndef COMMAND_H
#define COMMAND_H

#include "ICommand.h"
#include "InformationHeaders/commandPar.h"

#include "Bases/GameBase.h"
#include "GameField/GameFieldProxy.h"
#include "Game/game.h"

class FacadeMediator;

class Command : public ICommand
{
public:
    Command() = default;
    virtual std::vector<size_t> exec() = 0;

protected:
    Game* game;
    Request request;
    std::vector<size_t> param;
    FacadeMediator *facadeMediator;
};

class GameCommand : public Command
{
public:
    GameCommand(UIFacade *facade, Game *game, Request request, std::vector<size_t> param);
    std::vector<size_t> exec() override;
};

class BaseCommand : public Command
{
public:
    BaseCommand(FacadeMediator* facade, GameBase* base, Request request, std::vector<size_t> param);
    std::vector<size_t> exec();
};

class FieldCommand : public Command
{
public:
    FieldCommand(FacadeMediator* facade, GameFieldProxy field, Request request, std::vector<size_t> param);
};

#endif // COMMAND_H
