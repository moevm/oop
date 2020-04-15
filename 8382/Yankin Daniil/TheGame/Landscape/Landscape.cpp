#include "Landscape.h"


Landscape::Landscape(Point point) : point(point) {}

Point Landscape::getPoint() {
    return point;
}

int8_t Landscape::getMovementCost() {
    return movementCost;
}
