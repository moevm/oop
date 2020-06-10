#include "Invoker.h"

void Invoker::setField(GameField *f)
{
    field = f;
}

void Invoker::addBase(Base* b, Coordinates c, QPushButton* p)
{
    auto cmd = new AddBaseCommand(b, c, p);
    cmd->setField(field);
    cmd->exec();
    commands.push(cmd);
}

void Invoker::attackUnit(Coordinates a, Coordinates i)
{
    auto cmd = new AttackUnitCommand(a, i);
    cmd->setField(field);
    cmd->exec();
    commands.push(cmd);
}

void Invoker::createUnitToBase(Unit* u, Coordinates c)
{
    auto cmd = new CreateUnitToBaseCommand(u, c);
    cmd->setField(field);
    cmd->exec();
    commands.push(cmd);
}

void Invoker::deathUnit(Coordinates u, unsigned hpToRestore)
{
    auto cmd = new DeathUnitCommand(u, hpToRestore);
    cmd->setField(field);
    cmd->exec();
    commands.push(cmd);
}

void Invoker::destroyBase(Coordinates b, unsigned hp, std::vector<Object**> c)
{
    auto cmd = new DestroyBaseCommand(b, hp, c);
    cmd->setField(field);
    cmd->exec();
    commands.push(cmd);
}

void Invoker::entryFromBase(Object*& b, Coordinates c)
{
    auto cmd = new EntryFromBaseCommand(b, c);
    cmd->setField(field);
    cmd->exec();
    commands.push(cmd);
}

void Invoker::moveUnit(Coordinates c1, Coordinates c2)
{
    auto cmd = new MoveUnitCommand(c1, c2);
    cmd->setField(field);
    cmd->exec();
    commands.push(cmd);
}

void Invoker::undo()
{
    if (commands.empty()) return;
    commands.top()->unExec();
    delete commands.top();
    commands.pop();
}
