#include "Position.h"

Position::Position(int startX, int startY) {
    x = startX;
    y = startY;
}

int Position::getPositionX() const {
    return x;
}

int Position::getPositionY() const {
    return y;
}

void Position::setNewPositionX(int newPositionX) {
    Position::x = newPositionX;
}

void Position::setNewPositionY(int newPositionY) {
    Position::y = newPositionY;
}
