#ifndef COMMAND_H
#define COMMAND_H

#include "game.h"

class Command : public ICommand
{
    virtual std::vector<int> exec() = 0;
private:
    RequestType type;
    std::vector<int> param;
    IFacadeMediator *facadeMediator;
};

class GameCommand : public Command
{
public:
    GameCommand(UIFacade *facade, Game *game, RequestType type, std::vector<int> param, ILogAdapter *logger);
    std::vector<int> exec();
private:
    Game *game;
    RequestType type;
    std::vector<int> param;
    IFacadeMediator *facadeMediator;
    ILogAdapter *logger;
};

class BaseCommand : public Command
{
public:
    BaseCommand(IFacadeMediator *facade, Base *base, RequestType type, std::vector<int> param, ILogAdapter *logger, FieldItem *toFind = nullptr);
    std::vector<int> exec();
private:
    Base *base;
    RequestType type;
    std::vector<int> param;
    FieldItem *toFind;
    IFacadeMediator *facadeMediator;
    ILogAdapter *logger;
};

class FieldCommand : public Command
{
public:
    FieldCommand(IFacadeMediator *facade, Field *field, RequestType type, std::vector<int> param, ILogAdapter *logger, FieldItem *toFind = nullptr);
    std::vector<int> exec();
    FieldItem *findItem(int x, int y);
private:
    Field *field;
    RequestType type;
    std::vector<int> param;
    FieldItem *toFind;
    IFacadeMediator *facadeMediator;
    ILogAdapter *logger;
};

#endif // COMMAND_H
