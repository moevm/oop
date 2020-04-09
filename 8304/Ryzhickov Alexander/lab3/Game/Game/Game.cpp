//
// Created by Alex on 22.03.2020.
//

#include "Game.h"

Game::Game() {
    Game::field = new Field(10, 5, 10);
    Game::units = new Unit *[field->getMaxCountUnits()];
    Game::base = new Base(units, 0, 0, 10, field);
    field->setBase(0, 0, base);
}

Game::~Game() {
    int b = base->getCountUnitsInGame();
    for (int i = 0; i < b; ++i) {

        bool is = true;

        for (int num : base->vectorDeleteUnits) {
            if (i == num) {
                is = false;
                break;
            }
        }

        if (is) {
            delete (units[i]);
        }

    }
    delete (units);
    delete (field);
    delete (base);
}

void Game::getInformationAboutEnvironment(int *array, int x, int y) {
    array[0] = 0;
    array[1] = 0;
    array[2] = 0;
    array[3] = 0;

    int leftCellX = x - 1;
    int rightCellX = x + 1;
    int topCellY = y + 1;
    int bottomCellY = y - 1;

    /* GameCell *gameCell = field->getCell(x, y);
     Landscape *landscape = gameCell->getLanscape();
     bool sds = landscape->getInformationAboutLandscape();*/

    if (leftCellX >= 0 && leftCellX < field->getWidth()) {

        if (field->getCell(leftCellX, y)->getLanscape()->getInformationAboutLandscape()) {
            array[0] = 1;
            if (field->getCell(leftCellX, y)->getUnit() != nullptr) {
                array[0] = 2;
            }
        }
    }

    if (rightCellX >= 0 && rightCellX < field->getWidth()) {
        if (field->getCell(rightCellX, y)->getLanscape()->getInformationAboutLandscape()) {
            array[1] = 1;
            if (field->getCell(rightCellX, y)->getUnit() != nullptr) {
                array[1] = 2;
            }
        }
    }

    if (topCellY >= 0 && topCellY < field->getHeight()) {
        if (field->getCell(x, topCellY)->getLanscape()->getInformationAboutLandscape()) {
            array[2] = 1;
            if (field->getCell(x, topCellY)->getUnit() != nullptr) {
                array[2] = 2;
            }
        }
    }

    if (bottomCellY >= 0 && bottomCellY < field->getHeight()) {
        if (field->getCell(x, bottomCellY)->getLanscape()->getInformationAboutLandscape()) {
            array[3] = 1;
            if (field->getCell(x, bottomCellY)->getUnit() != nullptr) {
                array[3] = 2;
            }
        }
    }
}

void Game::updateUnitPosition(int lastX, int lastY, int newX, int newY) {
    field->updateUnitPosition(lastX, lastY, newX, newY);
}

void Game::addSwordsmen(int x,int y) {
    base->addSwordsmen(x,y);
}

void Game::addSpearmen(int x,int y) {
    base->addSpearmen(x,y);

}

void Game::addArcher(int x,int y) {
    base->addArcher(x,y);

}

void Game::addMagician(int x,int y) {
    base->addMagician(x,y);

}

void Game::addKing(int x,int y) {
    base->addKing(x,y);

}

void Game::addKnight(int x,int y){
    base->addKnight(x,y);
}

bool Game::attackUnit(int xPositionUnit1, int yPositionUnit1, int xPositionUnit2, int yPositionUnit2) {
    bool isAlive = true;

    Unit *unit1 = field->getCell(xPositionUnit1,yPositionUnit1)->getUnit();
    Unit *unit2 = field->getCell(xPositionUnit2,yPositionUnit2)->getUnit();

    unit1->attack(unit2);

    if (unit2->getHealth() <= 0){
        delete unit2;
        isAlive = false;
    }

    return isAlive;
}

int Game::getInformationAboutMoney() {
    return base->getMoney();
}

int Game::getInformationAboutBaseHealth() {
    return base->getHealthBase();
}



