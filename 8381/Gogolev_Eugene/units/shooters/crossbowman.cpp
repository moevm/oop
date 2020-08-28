#include "crossbowman.hpp"

static const char sprite[3][3] = {{' ', 'o', ' '},
                                  {'(', '|',  '\\'},
                                  {' ', '^',  ' '}};

const string Crossbowman::type = "Crossbowman";

Crossbowman::Crossbowman () {
    hp = Crossbowman::getMaxHP();
}

int Crossbowman::getMaxHP () {
    return 5;
}

int Crossbowman::getDamage () {
    return 4;
}

int Crossbowman::attackDistance () {
    return 4;
}

int Crossbowman::visionDistance () {
    return 4;
}

char Crossbowman::getChar (int x, int y) {
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

const string& Crossbowman::getType () {
    return type;
}


