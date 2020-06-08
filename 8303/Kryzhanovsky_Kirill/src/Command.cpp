//
// Created by therealyou on 06.04.2020.
//

#include "Command.h"


SetUnitCommand::SetUnitCommand(Base *base, UnitsType unitType, int x, int y, int unitId) :
        base(base), unitType(unitType), x(x), y(y), unitId(unitId) {}

SetUnitCommand::SetUnitCommand(GameField *gameField, char unitChar, int x, int y, int player) :
        gameField(gameField), unitChar(unitChar), x(x), y(y), player(player) {}

void SetUnitCommand::execute() {
    if (base) {
        base->createUnit(unitType, x, y, unitId);
    }
    else if (gameField) {
        ProfileUnit titanValues = {2000, 10, 1, 10, 10};
        Unit *unit = Fabric().createUnit(unitChar, titanValues);
        gameField->addUnit(unit, x, y);
        unit->addObserver(gameField);
        switch (player) {
            case 1:
                gameField->unit1 = unit;
                break;
            case 2:
                gameField->unit2 = unit;
                break;
            case 3:
                gameField->unit3 = unit;
                break;
            default:
                break;
        }

    }
}

SetBaseCommand::SetBaseCommand(int x, int y, int maxObjects, GameField *ptr, int number, int health) : x(x), y(y),
                                                                                                       maxObjects(
                                                                                                               maxObjects),
                                                                                                       gameField(ptr),
                                                                                                       baseNumber(
                                                                                                               number),
                                                                                                       health(health) {}

void SetBaseCommand::execute() {
    gameField->createBase(x, y, baseNumber, maxObjects, health);
}

MoveUpUnitCommand::MoveUpUnitCommand(GameField *ptr, Unit *unit) : gameField(ptr), unit(unit) {}

void MoveUpUnitCommand::execute() {
    gameField->moveUnit(unit, 0, -1);
}

MoveDownUnitCommand::MoveDownUnitCommand(GameField *ptr, Unit *unit) : gameField(ptr), unit(unit) {}

void MoveDownUnitCommand::execute() {
    gameField->moveUnit(unit, 0, 1);
}

MoveRightUnitCommand::MoveRightUnitCommand(GameField *ptr, Unit *unit) : gameField(ptr), unit(unit) {}

void MoveRightUnitCommand::execute() {
    gameField->moveUnit(unit, 1, 0);
}

MoveLeftUnitCommand::MoveLeftUnitCommand(GameField *ptr, Unit *unit) : gameField(ptr), unit(unit) {}

void MoveLeftUnitCommand::execute() {
    gameField->moveUnit(unit, -1, 0);
}

AttackUnitCommand::AttackUnitCommand(GameField *ptr, Unit *unit, int x, int y) : gameField(ptr), unit(unit), x(x),
                                                                                 y(y) {}

void AttackUnitCommand::execute() {
    if (gameField->isCorrect(x, y) && abs(unit->getX() - x) <= unit->profileUnit.attackRange &&
        abs(unit->getY() - y) <= unit->profileUnit.attackRange)
        gameField->attack(x, y, unit->profileUnit.damage);
    else
        std::cout << "out of attack range!" << std::endl;
}

ShowStatusCommand::ShowStatusCommand(GameField *ptr) : gameField(ptr) {}

void ShowStatusCommand::execute() {
    for (auto iter : *gameField) {
        if (iter.base) {
            iter.base->print(true);
        }
    }
}


void HelpCommand::execute() {
    std::cout << "Commands:" << std::endl;
    std::cout << "setBase - create new base" << std::endl;
    std::cout << "setUnit - create new Unit" << std::endl;
    std::cout << "move[Up/Down/Left/Right] - move unit Up/Down/Left/Right" << std::endl;
    std::cout << "attack - attack object on gameField" << std::endl;
    std::cout << "showStatus - show current game status" << std::endl;
    std::cout << "switchLog - switch log stream" << std::endl;
    std::cout << "turnLog - turn On/Off logging" << std::endl;
    std::cout << "save - save current game" << std::endl;
    std::cout << "load - load previous saved game" << std::endl;
}

SaveCommand::SaveCommand(GameField *gameField) : gameField(gameField) {}

void SaveCommand::execute() {
    SnapShot *snapShot = gameField->makeSnapShot("save");
    snapShot->save();
}

LoadCommand::LoadCommand(GameField *gameField) : gameField(gameField) {}

void LoadCommand::execute() {
    SnapShot *snapShot = gameField->makeSnapShot("load");
    try {
        snapShot->load();
    } catch (LogicException &exception) {
        std::cout << exception.what() << std::endl;
    } catch (TypeException &exception1) {
        std::cout << exception1.what() << std::endl;
    } catch (CheckException &exception2) {
        std::cout << exception2.what() << std::endl;

    }
}