#ifndef COMMAND_H
#define COMMAND_H

#include "Bases/GameBase.h"
#include "GameField/GameFieldProxy.h"
#include "ICommand.h"
#include "InformationHeaders/commandPar.h"
#include "Game/ChainHandler.h"

class FacadeMediator;
class Game;

class Command : public ICommand, public AbstractHandler
{
public:
    Command(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_ = NONE_UNIT, eBaseType baseType_ = NONE_BASE);
    Command() = default;
    void exec() override;

protected:
    std::shared_ptr<FacadeMediator> facadeMediator;
    eRequest request;
    std::vector<size_t> param;
    eUnitsType unitType;
    eBaseType baseType;
};

class GameCommand : public Command
{
public:
    GameCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_ = NONE_UNIT, eBaseType baseType_ = NONE_BASE);
    void exec() override;
};

class BaseCommand : public Command
{
public:
    BaseCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_ = NONE_UNIT, eBaseType baseType_ = NONE_BASE);
    void exec();
};

class FieldCommand : public Command
{
public:
    FieldCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_ = NONE_UNIT, eBaseType baseType_ = NONE_BASE);
    void exec();
};

#endif // COMMAND_H
