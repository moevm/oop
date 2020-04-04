#include "Plain.h"


Plain::Plain(Point point) : Landscape(point) {
    movementCost = 1;
}

bool Plain::movementAccess() {
    return true;
}

uint8_t Plain::getObjectType() {
    return LAND_PLAIN;
}
