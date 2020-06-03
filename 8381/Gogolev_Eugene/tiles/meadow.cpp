#include "meadow.hpp"

static const char sprite[3][3] = {{' ', ' ', ' '},
                                  {' ', ' ', ' '},
                                  {' ', ' ', ' '}};

char Meadow::getId () {
    return id;
}

char Meadow::getChar (int x, int y) {
    validateChar(x, y);
    return sprite[x][y];
}

bool Meadow::allow (DamageType damageType) {
    return true;
}

bool Meadow::allow (MovingType movingType) {
    return true;
}


