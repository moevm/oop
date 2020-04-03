#include "GameField.hpp"

GameField::GameField(int width, int height) : width(width), height(height) {
    gameField = new FieldCell * [height];
    for (int i = 0; i < height; i++)
        gameField[i] = new FieldCell [width];
    numUnits = 0;
    base = new Base;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            gameField[i][j].setCoordinates(i, j);
}

GameField::GameField(const GameField &field) {
    width = field.width;
    height = field.height;
    gameField = new FieldCell* [height];
    for (int i = 0; i < height; i++) {
        gameField[i] = new FieldCell[width];
        gameField[i] = field.gameField[i];
    }
    numUnits = field.numUnits;
    base = field.base;
}

GameField& GameField::operator=(const GameField &field) {
    if(&field == this)
        return *this;

    for (int i = 0; i < height; i++)
        delete [] gameField[i];
    delete [] gameField;

    width = field.width;
    height = field.height;
    for (int i = 0; i < height; i++) {
        gameField[i] = new FieldCell[width];
        gameField[i] = field.gameField[i];
    }
    numUnits = field.numUnits;
    base = field.base;
    return *this;
}


void GameField::createUnit(UnitName unitName, int x, int y){

    if (numUnits >= MAX_UNITS){
        std::cout << "You can't create new unit. Too much units." << std::endl;
        return;
    }

    if (!gameField[x][y].isEmpty()){
        std::cout << "This cell is not empty." << std::endl;
        return;
    }

    base->createUnit(&gameField[x][y], unitName);
}

void GameField::deleteUnit(int x, int y) {

    if (gameField[x][y].isEmpty()){
        std::cout << "This cell is empty." << std::endl;
        return;
    }

    base->deleteUnit(&gameField[x][y]);
    gameField[x][y].deleteUnit();

}

void GameField::moveUnit(int x1, int y1, int x2, int y2) {

    if (gameField[x1][y1].isEmpty()){
        std::cout << "This cell is empty." << std::endl;
        return;
    }
    if (!(gameField[x2][y2].isEmpty())){
        std::cout << "This cell is not empty." << std::endl;
        return;
    }

    base->moveUnit(&gameField[x2][y2], &gameField[x1][y1]);

}

void GameField::setBase(int x, int y) {
    if (gameField[x][y].isObject())
        gameField[x][y].deleteObject();
    gameField[x][y].setBase();
}

void GameField::attackUnit(int x1, int y1, int x2, int y2) {
    if (gameField[x1][y1].isEmpty()){
        std::cout << "This cell is empty." << std::endl;
        return;
    }
    if ((gameField[x2][y2].isEmpty())){
        std::cout << "No unit to attack." << std::endl;
        return;
    }
    base->attackUnit(&gameField[x1][y1], &gameField[x2][y2]);
}

void GameField::makeActionWithObj(int x, int y) {
    if (!(gameField[x][y].isObject())){
        std::cout << "No objects" << std::endl;
        return;
    }
    if (gameField[x][y].isEmpty()){
        std::cout << "No unit" << std::endl;
        return;
    }
    *(gameField[x][y].getUnit()) += *(gameField[x][y].getObject());

}
