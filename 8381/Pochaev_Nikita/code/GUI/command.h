#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "Bases/GameBase.h"
#include "GameField/GameFieldProxy.h"
#include "ICommand.h"
#include "InformationHeaders/commandPar.h"

class FacadeMediator;
class Game;

class Command : public ICommand
{
public:
    Command(eRequest request_, std::vector<size_t> param_, eUnitsType unitType_ = NONE_UNIT, eBaseType baseType_ = NONE_BASE);
    Command(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_);
    Command() = default;
    void exec() override;

    void setMediator(std::shared_ptr<FacadeMediator> mediator);

    static std::string convertInfoRequestEnumToString(eRequest request);

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
