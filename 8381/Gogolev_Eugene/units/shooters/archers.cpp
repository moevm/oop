#include "archers.hpp"

static const char sprite[3][3] = {{' ', '@', ' '},
                                  {'/', '|', '>'},
                                  {' ', '^', ' '}};

const string Archers::type = "Archers";

Archers::Archers () {
    hp = Archers::getMaxHP();
}

int Archers::getMaxHP () {
    return 4;
}

int Archers::getDamage () {
    return 1;
}

int Archers::attackDistance () {
    return 3;
}

int Archers::visionDistance () {
    return 4;
}

char Archers::getChar (int x, int y) {
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

const string& Archers::getType () {
    return type;
}


