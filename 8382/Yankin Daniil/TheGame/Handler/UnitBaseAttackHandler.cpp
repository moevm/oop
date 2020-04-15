#include "UnitBaseAttackHandler.h"
#include "Unit/IUnit.h"
#include "Base/Base.h"
#include "RouteHandler.h"


void UnitBaseAttackHandler::handle(IUnit* attacker, Base* base) {
    if (attacker->getAttackRadius() == 0) {
        RouteHandler routeHandler;
        bool success = routeHandler.handle(attacker, base->getPoint(), false);
        if (!success)
            return;
    }
    Game::getInstance().getGameMediator().unitAttack(attacker, static_cast<Base*>(base));
}
