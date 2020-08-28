#include "villager.hpp"

static const char sprite[3][3] = {{' ', 'o', ' '},
                                  {'/', '~', '\\'},
                                  {' ', '^', ' '}};

const string Villager::type = "Villager";

Villager::Villager () {
    hp = Villager::getMaxHP();
    team = NEUTRAL;
}

int Villager::getMaxHP () {
    return 10;
}

char Villager::getChar (int x, int y) {
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

MovingType Villager::getMovingType () {
    return HORSE;
}


const string& Villager::getType () {
    return type;
}



