//
// Created by therealyou on 06.04.2020.
//

#ifndef LAB1_COMMAND_H
#define LAB1_COMMAND_H

#include <string>
#include "GameField.h"
#include "Exception.h"
#include "SnapShot.h"

class Command {
public:
    virtual void execute() = 0;
};

class SetUnitCommand : public Command {
    Base *base = nullptr;
    GameField *gameField = nullptr;
    UnitsType unitType;
    int x, y, unitId, player;
    char unitChar;
public:
    SetUnitCommand(Base *base, UnitsType unitType, int x, int y, int unitId);

    SetUnitCommand(GameField *gameField, char unitChar, int x, int y, int player);

    void execute() override;
};

class SetBaseCommand : public Command {
    int baseNumber;
    int x, y;
    int maxObjects;
    int health;
    GameField *gameField;

public:
    SetBaseCommand(int, int, int, GameField *, int, int);

    void execute() override;
};

class MoveUpUnitCommand : public Command {
    GameField *gameField;
    Unit *unit;
public:
    MoveUpUnitCommand(GameField *, Unit *);

    void execute() override;
};

class MoveDownUnitCommand : public Command {
    GameField *gameField;
    Unit *unit;
public:
    MoveDownUnitCommand(GameField *, Unit *);

    void execute() override;
};

class MoveRightUnitCommand : public Command {
    GameField *gameField;
    Unit *unit;
public:
    MoveRightUnitCommand(GameField *, Unit *);

    void execute() override;
};

class MoveLeftUnitCommand : public Command {
    GameField *gameField;
    Unit *unit;
public:
    MoveLeftUnitCommand(GameField *, Unit *);

    void execute() override;
};

class AttackUnitCommand : public Command {
    GameField *gameField;
    Unit *unit;
    int x, y;
public:
    AttackUnitCommand(GameField *, Unit *, int, int);

    void execute() override;
};

class ShowStatusCommand : public Command {
    GameField *gameField;
public:
    explicit ShowStatusCommand(GameField *);

    void execute() override;
};

class HelpCommand : public Command {
public:
    void execute() override;
};

class SaveCommand : public Command {
    GameField *gameField;
public:
    explicit SaveCommand(GameField *);

    void execute() override;
};

class LoadCommand : public Command {
    GameField *gameField;
public:
    explicit LoadCommand(GameField *);

    void execute() override;
};

#endif //LAB1_COMMAND_H
