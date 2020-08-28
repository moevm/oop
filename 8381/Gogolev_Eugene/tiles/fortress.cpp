#include "fortress.hpp"
#include "../exceptions/out_of_bounds_exception.hpp"

static const char sprite[3][3] = {{'#', '#', '#'},
                                  {'#', ' ', '#'},
                                  {'#', '#', '#'}};

char Fortress::getId () {
    return id;
}

char Fortress::getChar (int x, int y) {
    validateChar(x, y);
    return sprite[x][y];
}

bool Fortress::allow (DamageType damageType) {
    return damageType != ARROW;
}

bool Fortress::allow (MovingType movingType) {
    return movingType != HORSE;
}

