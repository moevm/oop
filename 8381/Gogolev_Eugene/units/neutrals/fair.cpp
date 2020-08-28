#include "fair.hpp"

static const char sprite[3][3] = {{'|', 'F', '|'},
                                  {'|', '%', '|'},
                                  {'|', '_', '|'}};

const string Fair::type = "Fair";

Fair::Fair () {
    hp = Fair::getMaxHP();
    team = NEUTRAL;
}

int Fair::getMaxHP () {
    return 5;
}

char Fair::getChar (int x, int y) {
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

const string& Fair::getType () {
    return type;
}


