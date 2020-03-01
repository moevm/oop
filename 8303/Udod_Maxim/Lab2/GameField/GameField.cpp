//
// Created by shenk on 14.02.2020.
//

#include <iostream>
#include "GameField.h"

GameField *GameField::gameField = nullptr;

GameField::GameField():
fieldHeight(0),
fieldWidth(0),
field(nullptr)
{}

GameField::GameField(int fieldSize):
fieldHeight(fieldSize),
fieldWidth(fieldSize)
{

    field = new FieldCell* [fieldSize];
    for (int i=0; i<fieldSize; i++){
        field[i] = new FieldCell [fieldSize];
    }
}

GameField::GameField(int fieldHeight, int fieldWidth):
fieldHeight(fieldHeight),
fieldWidth(fieldWidth)
{
    field = new FieldCell* [fieldHeight];
    for (int i=0; i<fieldHeight; i++){
        field[i] = new FieldCell [fieldWidth];
    }
}

void GameField::deleteObject(int x, int y) {

    delete field[y][x].getObject();
    field[y][x].eraseObject();

}

void GameField::addObject(GameObject *object, int x, int y) {

    if (object->isOnField){
        std::cout << "GameField: Object " << object << " already on field." << std::endl;
        return;
    }

    bool isInBorder = x < fieldWidth && y < fieldHeight && x >= 0 && y >= 0;

    if (isInBorder && field[y][x].isEmpty()){

        field[y][x].setObject(object);
        object->position = Point(x, y);
        object->isOnField = true;

    } else{

        std::cout << "Impossible to add Object " << object << " to field." << std::endl;

    }
}

void GameField::deleteObject(GameObject *object) {

    deleteObject(object->position.x, object->position.y);

}

void GameField::moveObject(const Point &p1, const Point &p2) {

    if (!field[p1.y][p1.x].isEmpty() && field[p2.y][p2.x].isEmpty()){

        field[p2.y][p2.x] = std::move(field[p1.y][p1.x]);
        field[p2.y][p2.x].getObject()->position = p2;

        field[p1.y][p1.x].eraseObject();

    } else{

        std::cout << "GameField: Impossible to move object." << std::endl;

    }

}

void GameField::moveObject(GameObject *object, const Point &p2) {

    Point p1 = object->getPosition();
    moveObject(p1, p2);

}

void GameField::deleteObject(const Point &point) {

    deleteObject(point.x, point.y);

}

int GameField::getHeight() const{
    return fieldHeight;
}

int GameField::getWidth() const{
    return fieldWidth;
}

FieldCell *GameField::getCell(const Point &p) const{

    if (p.x < fieldWidth && p.y < fieldHeight)
        return &field[p.y][p.x];
    return nullptr;
}

GameField::~GameField() {

    for (int i=0; i<fieldHeight; i++){
        delete []field[i];
    }

    delete []field;

}

void GameField::init(int fieldHeight, int fieldWidth) {

    if (!gameField){

        gameField = new GameField(fieldHeight, fieldWidth);

    } else{

        std::cout << "Game field already initialized" << std::endl;

    }
}

GameField *GameField::getInstance() {
    if (gameField){
        return gameField;
    } else{
        std::cout << "Game field is not initialized" << std::endl;
        return nullptr;
    }
}