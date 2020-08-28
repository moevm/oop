#include "sheep.hpp"

static const char sprite[3][3] = {{' ', '@', '>'},
                                  {'@', 'w', '@'},
                                  {'/', '@', '\\'}};

const string Sheep::type = "Sheep";

Sheep::Sheep () {
    hp = Sheep::getMaxHP();
    team = NEUTRAL;
}

int Sheep::getMaxHP () {
    return 50;
}

int Sheep::getDamage () {
    return 1;
}

DamageType Sheep::getDamageType () {
    return PRICKING;
}

MovingType Sheep::getMovingType () {
    return HORSE;
}

char Sheep::getChar (int x, int y) {
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

const string& Sheep::getType () {
    return type;
}


