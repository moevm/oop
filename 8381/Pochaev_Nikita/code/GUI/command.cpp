#include "command.h"
#include "Game/FacadeMediator.h"

/**
 * Depending on which mediator was transferred to the command,
 * the corresponding command will be called
 */

Command::Command(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    facadeMediator(std::move(facadeMediator_)), request(request_), param(param_), unitType(unitType_), baseType(baseType_) { };

GameCommand::GameCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    Command(facadeMediator_, request_, param_, unitType_, baseType_) { };

BaseCommand::BaseCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    Command(facadeMediator_, request_, param_, unitType_, baseType_) { };

FieldCommand::FieldCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    Command(facadeMediator_, request_, param_, unitType_, baseType_) { };

void Command::exec()
{
    BaseCommand baseCommand(facadeMediator, request, param, unitType, baseType);
    baseCommand.exec();
}

void BaseCommand::exec()
{
    if(request == ADD_UNIT)
    {
        facadeMediator->sendRequest(param, unitType, baseType);
        return;
    }
    else if(request == BASE_INFO && request == UNIT_INFO)
    {
        facadeMediator->sendInfoRequest(request, param[0], param[1]);
        return;
    }
    GameCommand gameCommand(facadeMediator, request, param, unitType, baseType);
    gameCommand.exec();
}

void GameCommand::exec()
{
    if(request == ATTACK_UNIT)
    {
        facadeMediator->sendRequest(param, unitType, baseType);
    }
    else if(request == GAME_INFO)
    {
        facadeMediator->sendInfoRequest(request, param[0], param[1]);
    }
    else if(request == MOVE_UNIT)
    {
        facadeMediator->sendRequest(param, unitType, baseType);
    }
    FieldCommand fieldCommand(facadeMediator, request, param, unitType, baseType);
    fieldCommand.exec();
}

void FieldCommand::exec()
{
    if(request == ITEM_INFO || request == UNIT_INFO || request == BASE_INFO)
    {
        facadeMediator->sendInfoRequest(request, param[0], param[1]);
    }
    return;
}
