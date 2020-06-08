//
// Created by therealyou on 01.06.2020.
//

#include "Rules.h"


Rule::Rule() : state1(new State1), state2(new State2), state3(new State3), current(state1) {}

void Rule::nextPlayer(int playersNumber) {
    if (current == state1) {
        std::cout << "second player's turn" << std::endl;
        current = state2;
    } else if (current == state2 && playersNumber == 3) {
        std::cout << "third player's turn " << std::endl;
        current = state3;
    } else {
        std::cout << "first player's turn " << std::endl;
        current = state1;
    }
}

GameField *Rule1::createField(Adapter *adapter) {
    auto *field = new GameField(5, 5, adapter, 1);
    return field;
}

void Rule1::handle(std::string command, BaseHandler *handler, int playersNumber, std::string mode) {
    current->handle(command, handler, mode);
    if (command == "attack" || command == "moveUp" || command == "moveDown" || command == "moveLeft" ||
        command == "moveRight" || command == "setUnit")
        nextPlayer(playersNumber);
}

int Rule1::loser(GameField *field, int playersNumber) {
    if ((!field->findBase(1)))
        return 1;
    else if (!field->findBase(2))
        return 2;
    else if (playersNumber == 3 && !field->findBase(3))
        return 3;
    return 0;
}

GameField *Rule2::createField(Adapter *adapter) {
    auto *field = new GameField(3, 5, adapter, 2);
    return field;
}

void Rule2::handle(std::string command, BaseHandler *handler, int playersNumber, std::string mode) {
    current->handle(command, handler, mode);
    if (command == "attack" || command == "moveUp" || command == "moveDown" || command == "moveLeft" ||
        command == "moveRight")
        nextPlayer(playersNumber);
}

int Rule2::loser(GameField *gameField, int playersNumber) {
    if (!gameField->findUnit(gameField->unit1->getId()))
        return 1;
    else if (!gameField->findUnit(gameField->unit2->getId()))
        return 2;
    else if (playersNumber == 3 && !gameField->findUnit(gameField->unit3->getId()))
        return 3;
    return 0;
}