//
// Created by anton on 03.04.2020.
//

#ifndef OOP_1_COMMAND_H
#define OOP_1_COMMAND_H

#include "Field.h"
#include <iostream>

class Command {
public:
    virtual void execute() = 0;
};

class SetUnitCommand: public Command
{
    Base* ptr;
    Field* field;
    char className;
    std::string unitName;
    int unitX, unitY, player;
public:
    SetUnitCommand(Base*, char, std::string&);
    SetUnitCommand(Field* field1, int player, char className, std::string&, int, int);
    void execute() override;
};

class SetBaseCommand: public Command
{
    int baseNumber;
    int x, y;
    int maxObjects;
    Field* ptr;
public:
    SetBaseCommand(int, int, int, Field*, int);
    void execute() override;
};

class MoveUpUnitCommand: public Command
{
    Field* ptr;
    Unit* unit;
public:
    MoveUpUnitCommand(Field*, Unit*);
    void execute() override;
};

class MoveDownUnitCommand: public Command
{
    Field* ptr;
    Unit* unit;
public:
    MoveDownUnitCommand(Field*, Unit*);
    void execute() override;
};

class MoveRightUnitCommand: public Command
{
    Field* ptr;
    Unit* unit;
public:
    MoveRightUnitCommand(Field*, Unit*);
    void execute() override;
};

class MoveLeftUnitCommand: public Command
{
    Field* ptr;
    Unit* unit;
public:
    MoveLeftUnitCommand(Field*, Unit*);
    void execute() override;
};

class AttackUnitCommand: public Command
{
    Field* ptr;
    Unit* unit;
    int x, y;
public:
    AttackUnitCommand(Field*, Unit*, int, int);
    void execute() override;
};

class ShowStatusCommand: public Command
{
    Field* ptr;
public:
    explicit ShowStatusCommand(Field*);
    void execute() override;
};

class HelpCommand: public Command
{
public:
    void execute() override;
};

class SaveCommand: public Command
{
    Field* field;
public:
    explicit SaveCommand(Field*);
    void execute() override;
};

class LoadCommand: public Command
{
    Field* field;
public:
    explicit LoadCommand(Field*);
    void execute() override;
};
#endif //OOP_1_COMMAND_H