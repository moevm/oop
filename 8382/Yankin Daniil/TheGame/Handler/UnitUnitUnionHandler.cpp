#include "UnitUnitUnionHandler.h"
#include "Unit/UnitHeader.h"
#include "Handler/RouteHandler.h"


void UnitUnitUnionHandler::handle(IUnit* active, IUnit* passive) {
    RouteHandler routeHandler;
    bool success = routeHandler.handle(active, passive->getPoint(), false);
    if (!success)
        return;
    active->unite(passive);
}
