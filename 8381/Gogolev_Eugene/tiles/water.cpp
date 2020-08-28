#include "water.hpp"

static const char sprite[3][3] = {{'~', ' ', '~'},
                                  {' ', '~', ' '},
                                  {'~', ' ', '~'}};

char Water::getId () {
    return id;
}

char Water::getChar (int x, int y) {
    validateChar(x, y);
    return sprite[x][y];
}

bool Water::allow (DamageType damageType) {
    return true;
}

bool Water::allow (MovingType movingType) {
    return movingType != HORSE;
}

