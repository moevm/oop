#include "Game/FacadeMediator.h"

FacadeMediator::FacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_) :
    game(std::move(game_)), command(std::move(command_)), facade(std::move(facade_)) { }

addUnitFacadeMediator::addUnitFacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_) :
    FacadeMediator(game_, command_, facade_) { }

unitAttackFacadeMediator::unitAttackFacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_) :
    FacadeMediator(game_, command_, facade_) { }

unitMoveFacadeMediator::unitMoveFacadeMediator(std::shared_ptr<Game> game_, std::shared_ptr<Command> command_, std::shared_ptr<UIFacade> facade_) :
    FacadeMediator(game_, command_, facade_) { }

std::string FacadeMediator::sendRequest([[maybe_unused]] std::vector<size_t> param, [[maybe_unused]] eUnitsType unitType, [[maybe_unused]] eBaseType baseType)
{
    return "Nothing was done!";
}

std::string addUnitFacadeMediator::sendRequest(std::vector<size_t> param, eUnitsType unitType, [[maybe_unused]] eBaseType baseType)
{
    game->createUnit(unitType, param[0], param[1]);
    facade->receiveStrAnswer("Unit was successfully created!");
    return "Unit was successfully created!";
}

std::string unitAttackFacadeMediator::sendRequest(std::vector<size_t> param, [[maybe_unused]] eUnitsType unitType, [[maybe_unused]] eBaseType baseType)
{
    game->unitAttack(param[0], param[1], param[2], param[3]);
    facade->receiveStrAnswer("Unit was successfully created!");
    return "Unit attack has been successful";
}

std::string unitMoveFacadeMediator::sendRequest(std::vector<size_t> param, [[maybe_unused]] eUnitsType unitType, [[maybe_unused]] eBaseType baseType)
{
    game->moveUnit(param[0], param[1], param[2], param[3]);
    facade->receiveStrAnswer("Unit was successfully created!");
    return "Unit movement was successfully completed";
}

std::string FacadeMediator::sendInfoRequest([[maybe_unused]] eRequest request, size_t x, size_t y)
{
    if(request == GAME_INFO)
    {
        // TODO: game info
        facade->receiveStrAnswer("Game Info");
        return "Game Info";
    }
    else if(request == BASE_INFO)
    {
        facade->receiveStrAnswer(game->getBaseInfo(x, y));
        return game->getBaseInfo(x, y);
    }
    else if(request == UNIT_INFO)
    {
        facade->receiveStrAnswer(game->getUnitInfo(x, y));
        return game->getUnitInfo(x, y);
    }
    else if(request == LAND_INFO)
    {
        facade->receiveStrAnswer(game->getLandInfo(x, y));
        return game->getLandInfo(x, y);
    }
    else if(request == ITEM_INFO)
    {
        facade->receiveStrAnswer(game->getItemInfo(x, y));
    }

    return "Information about nothing";
}
