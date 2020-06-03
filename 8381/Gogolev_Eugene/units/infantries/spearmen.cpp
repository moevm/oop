#include "spearmen.hpp"

static const char sprite[3][3] = {{' ', '@', '^'},
                                  {'O', '|', '|'},
                                  {' ', '^', '|'}};

const string Spearmen::type = "Spearmen";

Spearmen::Spearmen () {
    hp = Spearmen::getMaxHP();
}

int Spearmen::getMaxHP () {
    return 4;
}

DamageType Spearmen::getDamageType () {
    return PRICKING;
}

int Spearmen::getDamage () {
    return 2;
}

char Spearmen::getChar (int x, int y) {
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

const string& Spearmen::getType () {
    return type;
}

