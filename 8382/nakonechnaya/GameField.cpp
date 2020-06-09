#include "GameField.h"

GameField::GameField(int width, int height) : width(width), height(height) {
    gameField = new FieldCell * [height];
    for (int i = 0; i < height; i++)
        gameField[i] = new FieldCell[width];
    numUnits = 0;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            gameField[i][j].setCoordinates(i, j);
}

void GameField::createUnit(UnitName unitName, int x, int y, Base *base){
    if (numUnits >= MAX_UNITS){
        std::cout << "You can't create new unit. Too much units." << std::endl;
        return;
    }

    if (!gameField[x][y].isEmpty()){
        std::cout << "This cell is not empty." << std::endl;
        return;
    }

    base->createUnit(&gameField[x][y], unitName);
    numUnits++;
    logString = base->getLogString();
}

void GameField::deleteUnit(int x, int y, Base *base) {

    if (gameField[x][y].isEmpty()){
        std::cout << "This cell is empty." << std::endl;
        return;
    }

    base->deleteUnit(&gameField[x][y]);
    logString = base->getLogString();
    gameField[x][y].deleteUnit();
    numUnits--;
}

void GameField::moveUnit(int x1, int y1, int x2, int y2, Base *base) {

    if (gameField[x1][y1].isEmpty()){
        std::cout << "This cell is empty." << std::endl;
        return;
    }
    if (!(gameField[x2][y2].isEmpty())){
        std::cout << "This cell is not empty." << std::endl;
        return;
    }

    base->moveUnit(&gameField[x2][y2], &gameField[x1][y1]);
    logString = base->getLogString();
}

void GameField::setBase(int x, int y) {
    if (gameField[x][y].isObject())
        gameField[x][y].deleteObject();
    gameField[x][y].setBase();
}

void GameField::attackUnit(int x1, int y1, int x2, int y2, Base *base, Base *enemyBase) {
    if (gameField[x1][y1].isEmpty()){
        std::cout << "This cell is empty." << std::endl;
        return;
    }
    if ((gameField[x2][y2].isEmpty())){
        if (!gameField[x2][y2].isBase()){
            std::cout << "No unit to attack." << std::endl;
            return;
        }
    }

    if (base->getUnit(x1, y1) == nullptr){
        std::cout << "The base doesnt have access to attacking unit." << std::endl;
        return;
    }

    if (enemyBase->getUnit(x2, y2) == nullptr){
        std::cout << "You cant attack your own unit." << std::endl;
        return;
    }

    base->attackUnit(&gameField[x1][y1], &gameField[x2][y2], enemyBase);
    if (gameField[x2][y2].isEmpty())
        numUnits--;
    if (gameField[x1][y1].isEmpty())
        numUnits--;
    logString = base->getLogString();
}

void GameField::attackBase(int x1, int y1, int x2, int y2, Base *base, Base *enemyBase) {
    if (gameField[x1][y1].isEmpty()){
        std::cout << "This cell is empty." << std::endl;
        return;
    }

    if (base->getUnit(x1, y1) == nullptr){
        std::cout << "The base doesnt have access to attacking unit." << std::endl;
        return;
    }

    base->attackEnemyBase(&gameField[x1][y1], &gameField[x2][y2], enemyBase);
    if (gameField[x1][y1].isEmpty())
        numUnits--;
    logString = base->getLogString();
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

    logString = "Unit from cell (";
    logString += (std::to_string(gameField[x][y].getUnit()->getCoordinates()->x) + ",");
    logString += (std::to_string(gameField[x][y].getUnit()->getCoordinates()->y) + ") visited the ");
    switch (gameField[x][y].getObject()->getObjName()){
        case BAR:
            logString += "bar ";
            break;
        case HOSPITAL:
            logString += "hospital ";
            break;
        case SHOP:
            logString += "shop ";
            break;
        case TRAIN:
            logString += "training base ";
            break;
    }
    logString += "from cell (";
    logString += (std::to_string(gameField[x][y].getCoordinates()->x) + ",");
    logString += (std::to_string(gameField[x][y].getCoordinates()->y) + ").");
}