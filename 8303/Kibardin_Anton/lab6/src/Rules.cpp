//
// Created by anton on 05.05.2020.
//
#include "Rules.h"

Rule::Rule(): state1(new State1), state2(new State2), state3(new State3), current(state1){}

void Rule::nextPlayer(int playersNumber)
{
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

Field * Rule1::createField(Adapter *adapter) {
    auto* field = new Field(5, 5, adapter, 1);
    return field;
}

void Rule1::handle(std::string command, BaseHandler *handler, int playersNumber, std::string mode) {
    current->handle(command, handler, mode);
    if(command == "attack" || command == "moveUp"|| command == "moveDown" || command == "moveLeft" || command == "moveRight" || command == "setUnit")
        nextPlayer(playersNumber);
}

int Rule1::loser(Field *field, int playersNumber) {
    if((!field->findBase(1)))
        return 1;
    else if(!field->findBase(2))
        return 2;
    else if(playersNumber == 3 && !field->findBase(3))
        return 3;
    return 0;
}

Field * Rule2::createField(Adapter *adapter) {
    auto* field = new Field(3, 5, adapter, 2);
    return field;
}

void Rule2::handle(std::string command, BaseHandler *handler, int playersNumber, std::string mode) {
    current->handle(command, handler, mode);
    if(command == "attack" || command == "moveUp"|| command == "moveDown" || command == "moveLeft" || command == "moveRight")
        nextPlayer(playersNumber);
}

int Rule2::loser(Field *field, int playersNumber) {
    if(!field->findUnit(field->unit1))
        return 1;
    else if(!field->findUnit(field->unit2))
        return 2;
    else if(playersNumber == 3 && !field->findUnit(field->unit3))
        return 3;
    return 0;
}