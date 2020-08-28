#include "knight.hpp"

static const char sprite[3][3] = {{' ', '@', ' '},
                                  {' ', '|', '>'},
                                  {' ', '^', ' '}};

const string Knight::type = "Knight";

int Knight::getMaxHP () {
    return 8;
}

DamageType Knight::getDamageType () {
    return PRICKING;
}

char Knight::getChar (int x, int y) {
    validateChar(x, y);
    if (x == 1 && y == 1) {
        switch (team) {
            case RED:
                return 'A';
            case BLUE:
                return '0';
            default:
                return '?';
        }
    }
    return sprite[y][x];
}

Knight::Knight () {
    hp = Knight::getMaxHP();
}

const string& Knight::getType () {
    return type;
}
