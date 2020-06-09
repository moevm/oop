#include "NeutralObject.h"

void NeutralObject::setCoordinates(int x, int y) {
    coordinates = new Coordinates;
    coordinates->x = x;
    coordinates->y = y;
}