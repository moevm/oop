#include "Mountain.h"


Mountain::Mountain(Point point) : Landscape(point) {
    movementCost = 0;
}

bool Mountain::movementAccess() {
    return true;
}

uint8_t Mountain::getObjectType() {
    return LAND_MOUNTAIN;
}
