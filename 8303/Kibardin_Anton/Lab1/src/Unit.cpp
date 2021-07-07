//
// Created by anton on 16.02.2020.
//

#include <cstdio>
#include "Unit.h"
Unit::Unit():health(200), armor(200), attack(20), attackRange(2), gameField(nullptr)
{}
int Unit::getX() const {
    if(gameField != nullptr)
        return this->x;
    return -1;
}

int Unit::getY() const {
    if(gameField != nullptr)
        return this->y;
    return -1;
}

void Unit::setX(int x) {
    this->x = x;
}

void Unit::setY(int y) {
    this->y = y;
}

void Unit::move(int X, int Y){
    if(gameField != nullptr && gameField->checkPoint(X, Y))
    {
        printf("start coord:%d %d\n", this->x, this->y);

        gameField->swapCharacters(this->x,this->y, X, Y);
        this->y = Y;
        this->x = X;
    }
}

bool Unit::isOnField() {
    return gameField != nullptr;
}

 void Unit::deleteFromField() {
    gameField->deleteObject(this);
    gameField = nullptr;
}

void Unit::replace(Field *gameField) {
    this->gameField = gameField;
}