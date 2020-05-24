#include "command.h"
#include "Game/FacadeMediator.h"

/**
 * Depending on which mediator was transferred to the command,
 * the corresponding command will be called
 */

Command::Command(eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    request(request_), param(param_), unitType(unitType_), baseType(baseType_) { };

Command::Command(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    Command(request_, param_, unitType_, baseType_)
{
    facadeMediator = std::move(facadeMediator_);
};

void Command::setMediator(std::shared_ptr<FacadeMediator> mediator)
{
    facadeMediator = std::move(mediator);
}

GameCommand::GameCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    Command(facadeMediator_, request_, param_, unitType_, baseType_) { };

BaseCommand::BaseCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    Command(facadeMediator_, request_, param_, unitType_, baseType_) { };

FieldCommand::FieldCommand(std::shared_ptr<FacadeMediator> facadeMediator_, eRequest request_, std::vector<size_t> param_, eUnitsType unitType_, eBaseType baseType_) :
    Command(facadeMediator_, request_, param_, unitType_, baseType_) { };

void Command::exec()
{
    if(!facadeMediator)
    {
        throw std::runtime_error("Using a command without a mediator installed");
    }

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

std::string Command::convertInfoRequestEnumToString(eRequest request_)
{
    if(request_ == GAME_INFO)
    {
        return "game info";
    }
    else if(request_ == BASE_INFO)
    {
        return "base info";
    }
    else if(request_ == UNIT_INFO)
    {
        return "unit info";
    }
    else if(request_ == LAND_INFO)
    {
        return "land info";
    }
    else if(request_ == ITEM_INFO)
    {
        return "item info";
    }

    return "";
}
