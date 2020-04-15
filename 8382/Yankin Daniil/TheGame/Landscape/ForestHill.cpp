#include "ForestHill.h"


ForestHill::ForestHill(Point point) : Landscape(point) {
    movementCost = 2;
}

bool ForestHill::movementAccess() {
    return true;
}

uint8_t ForestHill::getObjectType() {
    return LAND_FOREST_HILL;
}
