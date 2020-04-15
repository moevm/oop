#pragma once

#include "Object/Object.h"
#include <vector>

class IUnit;
class Base;



class UiCommand
{
public:
    UiCommand(uint8_t command, Object* object = nullptr, uint8_t parameter = 0);
    void execute();

private:
    uint8_t command;
    Object* object;
    uint8_t parameter;
};



class GameCommand
{
public:
    GameCommand(uint8_t command);
    void execute();

private:
    uint8_t command;
};



class UnitMoveCommand
{
public:
    UnitMoveCommand(IUnit* unit, std::vector <Point>* route);
    bool execute();

private:
    IUnit* unit;
    std::vector <Point>* route;
};



class BaseProduceCommand
{
public:
    BaseProduceCommand(Base* base, uint8_t unitType);
    void execute();

private:
    Base* base;
    uint8_t unitType;
};



enum UiCommands {
    UI_NONE,
    UI_TURN,
    UI_SELECT_OBJECT,
    UI_INTERACT_OBJECT,
    UI_PRODUCE
};

enum FacadeCommands {
    FACADE_TURN,
    FACADE_UNIT_MOVE,
    FACADE_UNIT_ATTACK,
    FACADE_UNIT_UNITE,
    FACADE_BASE_PRODUCE
};
