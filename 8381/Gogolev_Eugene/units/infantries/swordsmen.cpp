#include "swordsmen.hpp"

static const char sprite[3][3] = {{'|', 'o', ' '},
                                  {'W', '|', '\\'},
                                  {' ', '^', ' '}};

const string Swordsmen::type = "Swordsmen";

Swordsmen::Swordsmen () {
    hp = Swordsmen::getMaxHP();
}

int Swordsmen::getMaxHP () {
    return 5;
}

DamageType Swordsmen::getDamageType () {
    return CUTTING;
}

int Swordsmen::getDamage () {
    return 3;
}

char Swordsmen::getChar (int x, int y) {
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

const string& Swordsmen::getType () {
    return type;
}


