#include "UnitLandscapeHandler.h"
#include "Landscape/ILandscape.h"
#include "Unit/UnitHeader.h"
#include "RouteHandler.h"


void UnitLandscapeHandler::handle(IUnit* unit, ILandscape* land) {
    RouteHandler routeHandler;
    routeHandler.handle(unit, land->getPoint(), true);
}
