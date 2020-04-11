//
// Created by andrei on 04.04.2020.
//

#include "game.h"

void Game::addUnit(int x, int y, char type, int baseNum) {
    Unit* newUnit = this->field->getBase(baseNum)->createUnit(type);
    if (newUnit == nullptr) return;
    this->field->getCell(x,y)->setUnit(newUnit);
    this->field->getCell(x,y)->getLandscape()->unitCame(newUnit);
}

void Game::addNeutral(int x, int y, char type) {
    this->field->getCell(x,y)->setNeutral(Factory::createNeutral(type));
}

void Game::addBase(int x, int y) {
    this->field->addBase(x,y);
}

void Game::moveUnit(int x1, int y1, int x2, int y2) {
    Cell* cell1 = this->field->getCell(x1,y1);
    Cell* cell2 = this->field->getCell(x2,y2);
    if (!cell1->isUnit()) {
        return;
    }

    Unit* unit = cell1->getUnit();
    if (cell2->isUnit()) {
        if (unit->getBaseNum() != cell2->getUnit()->getBaseNum()) {
            pair<int,int> die = this->attack(unit, cell2->getUnit());
            if (die.second) {
                delete cell2->getUnit();
                cell2->setUnit(nullptr);
            }
            if (die.first) {
                delete unit;
                cell1->setUnit(nullptr);
                return;
            }
            if (!die.second) {
                return;
            }
        }
        else {
            return;
        }
    }

    if (cell2->isBase()) {
        if (unit->getBaseNum() != cell2->getBase()->getNum()) {
            cell2->getBase()->takeDamage(unit->getDamage());
        }
        return;
    }

    if (cell2->isNeutral()) {
        (*unit) += cell2->getNeutral();
        cell2->setNeutral(nullptr);
    }

    if (cell2->getLandscape()->getType() != 'w') {
        cell1->getLandscape()->unitLeft(unit);
        cell2->getLandscape()->unitCame(unit);
        cell2->setUnit(unit);
        cell1->setUnit(nullptr);
    }

}

pair<bool,bool> Game::attack(Unit *unit1, Unit *unit2) {
    bool FirstDie = unit1->takeDamage(unit2->getDamage());
    bool SecondDie = unit2->takeDamage(unit1->getDamage());
    return make_pair(FirstDie, SecondDie);
}

void Game::createField(int sizeX, int sizeY) {
    this->field = new Field(sizeX, sizeY);
}

void Game::printField() {
    this->field->printField();
}
