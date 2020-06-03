#include "rider.hpp"

static const char sprite[3][3] = {{'<', '@', ' '},
                                  {'<', '|', ' '},
                                  {'/', ' ', '\\'}};

const string Rider::type = "Rider";

Rider::Rider () {
    hp = Rider::getMaxHP();
}

int Rider::getMaxHP () {
    return 6;
}

DamageType Rider::getDamageType () {
    return CUTTING;
}

char Rider::getChar (int x, int y) {
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

const string& Rider::getType () {
    return type;
}


