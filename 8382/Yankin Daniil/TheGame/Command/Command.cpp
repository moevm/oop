#include "Command.h"
#include "Game/Game.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"


UiCommand::UiCommand(uint8_t command, Object* object, uint8_t parameter)
    : command(command), object(object), parameter(parameter) {}

void UiCommand::execute() {
    if (command == UI_TURN) {
        GameCommand gameCommand(FACADE_TURN);
        gameCommand.execute();
    }
    else {
        Game::getInstance().getGameFacade().userCommand(command, object, parameter);
    }
}



GameCommand::GameCommand(uint8_t command) : command(command) {}

void GameCommand::execute() {
    if (command == FACADE_TURN) {
        std::vector<int> logParameters;
        Game::getInstance().getLogAdapter().log(LOG_USER_TURN, logParameters);
        Game::getInstance().turn();
    }
}



UnitMoveCommand::UnitMoveCommand(IUnit* unit, std::vector <Point>* route)
    : unit(unit), route(route) {}

bool UnitMoveCommand::execute() {
    bool success = true;
    while (!route->empty() && success) {
        success = unit->move(route->back());
        route->pop_back();
    }
    return success;
}



BaseProduceCommand::BaseProduceCommand(Base* base, uint8_t unitType)
    : base(base), unitType(unitType) {}

void BaseProduceCommand::execute() {
    base->produceUnit(unitType);
}
