//
// Created by anton on 03.04.2020.
//

#include "Command.h"

SetUnitCommand::SetUnitCommand(Base* ptr, char className, std::string& unitName):field(nullptr), ptr(ptr), className(className), unitName(unitName){}

SetUnitCommand::SetUnitCommand(Field* field1, int player, char className, std::string &unitName, int x, int y):field(field1), ptr(nullptr), className(className), unitName(unitName), unitX(x), unitY(y), player(player){}

void SetUnitCommand::execute() {
    if(ptr)
    {
        ptr->createUnit(className, unitName);
    }
    else
    {
        Specifications titanValues = {2000, 500, 400, 1};
        Unit* unit = TitansFabric().createUnit(className, titanValues);
        field->addUnit(unit, unitX, unitY, unitName);
        switch (player) {
            case 1:
                field->unit1 = unit;
                break;
            case 2:
                field->unit2 = unit;
                break;
            case 3:
                field->unit3 = unit;
                break;
            default:
                break;
        }
    }
}

SetBaseCommand::SetBaseCommand(int x, int y, int maxObjects, Field* ptr, int number):x(x), y(y), maxObjects(maxObjects), ptr(ptr), baseNumber(number){}

void SetBaseCommand::execute() {
    ptr->setBase(x, y, maxObjects, baseNumber, 100);
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
    std::cout << "save - save current game" << std::endl;
    std::cout << "load - load previous saved game" << std::endl;
}

SaveCommand::SaveCommand(Field *tmp):field(tmp) {}

void SaveCommand::execute() {
    SnapShot* snapShot = field->makeSnapShot("save");
    snapShot->save();
}

LoadCommand::LoadCommand(Field *tmp):field(tmp){}

void LoadCommand::execute() {
    SnapShot* snapShot = field->makeSnapShot("load");
    try {
        snapShot->load();

    } catch (LogicException& exception) {
        std::cout << exception.what()<< std::endl;
    } catch (TypeException& exception1) {
        std::cout << exception1.what() << std::endl;
    } catch (CheckException& exception2) {
        std::cout << exception2.what() << std::endl;

    }
}