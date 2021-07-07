//
// Created by anton on 03.04.2020.
//

#include "Command.h"

SetUnitCommand::SetUnitCommand(Base* ptr, char className, std::string& unitName):ptr(ptr), className(className), unitName(unitName){}

void SetUnitCommand::execute() {
    ptr->createUnit(className, unitName);
}

SetBaseCommand::SetBaseCommand(int x, int y, int maxObjects, Field* ptr, int number):x(x), y(y), maxObjects(maxObjects), ptr(ptr), baseNumber(number){}

void SetBaseCommand::execute() {
    ptr->setBase(x, y, maxObjects, baseNumber);
}

MoveUpUnitCommand::MoveUpUnitCommand(Field* ptr, Unit* unit):ptr(ptr), unit(unit){}

void MoveUpUnitCommand::execute() {
    ptr->moveUnit(unit, unit->getX() - 1, unit->getY());
}

MoveDownUnitCommand::MoveDownUnitCommand(Field* ptr, Unit* unit):ptr(ptr), unit(unit){}

void MoveDownUnitCommand::execute() {
    ptr->moveUnit(unit, unit->getX() + 1, unit->getY());
}

MoveRightUnitCommand::MoveRightUnitCommand(Field* ptr, Unit* unit):ptr(ptr), unit(unit){}

void MoveRightUnitCommand::execute() {
    ptr->moveUnit(unit, unit->getX(), unit->getY() + 1);
}

MoveLeftUnitCommand::MoveLeftUnitCommand(Field* ptr, Unit* unit):ptr(ptr), unit(unit){}

void MoveLeftUnitCommand::execute() {
    ptr->moveUnit(unit, unit->getX(), unit->getY() - 1);
}

AttackUnitCommand::AttackUnitCommand(Field* ptr, Unit* unit, int x, int y):ptr(ptr), unit(unit), x(x), y(y){}

void AttackUnitCommand::execute() {
    if(ptr->checkPoint(x, y) && abs(unit->getX() - x) <= unit->values.attackRange && abs(unit->getY() - y) <= unit->values.attackRange)
    {

        ptr->attack(x,y, unit->values.attack);

    }
    else
        std::cout << "out of attack range!" << std::endl;
}

ShowStatusCommand::ShowStatusCommand(Field* ptr): ptr(ptr){}

void ShowStatusCommand::execute() {
    for(FieldIterator iter(ptr); iter != nullptr; iter++)
        if((*iter)->base)
        {
            (*iter)->base->printStatus();
        }
}


void HelpCommand::execute() {
    std::cout << "Commands:" << std::endl;
    std::cout << "setBase - create new base" << std::endl;
    std::cout << "setUnit - create new Unit" << std::endl;
    std::cout << "move[Up/Down/Left/Right] - move unit Up/Down/Left/Right" << std::endl;
    std::cout << "attack - attack object on field" << std::endl;
    std::cout << "showStatus - show current game status" << std::endl;
    std::cout << "switchLog - switch log stream" << std::endl;
    std::cout << "turnLog - turn On/Off logging" << std::endl;
}