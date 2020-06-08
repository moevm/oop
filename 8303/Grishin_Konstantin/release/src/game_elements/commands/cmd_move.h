#ifndef CMDMOVE_H
#define CMDMOVE_H

#include "game_elements/commands/command.h"

class Field;
class EntityInterface;
class Entity;

class CmdMove : public Command
{
    const std::string name_ = "move_command";

    Field * field;
    EntityInterface &entity;

    bool ableToMove = 1;
    float residualSteps = 0;

    Team team;

    int x;
    int y;

public:
    CmdMove(Field *field, EntityInterface &entity, int to_x, int to_y);
    bool execute(Logger *logger) override;
    const std::string & name() const override;

    bool valid_p() const;
    Team getTeam() const override;
};

#endif // CMDMOVE_H
