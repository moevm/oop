#include "Water.h"


Water::Water(Point point) : Landscape(point) {
    movementCost = 0;
}

bool Water::movementAccess() {
    return true;
}

uint8_t Water::getObjectType() {
    return LAND_WATER;
}
