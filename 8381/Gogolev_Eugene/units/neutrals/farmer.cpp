#include "farmer.hpp"

static const char sprite[3][3] = {{' ', '@', 'V'},
                                  {'/', '~', '|'},
                                  {' ', '^', '|'}};

const string Farmer::type = "Farmer";

Farmer::Farmer () {
    hp = Farmer::getMaxHP();
    team = NEUTRAL;
}

int Farmer::getMaxHP () {
    return 3;
}

DamageType Farmer::getDamageType () {
    return PRICKING;
}

MovingType Farmer::getMovingType () {
    return LEGS;
}

int Farmer::getDamage () {
    return 1;
}

char Farmer::getChar (int x, int y) {
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

const string& Farmer::getType () {
    return type;
}


