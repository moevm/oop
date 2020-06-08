#ifndef CMDWORK_H
#define CMDWORK_H

#include "game_elements/commands/command.h"

class Field;
class EntityInterface;

class CmdWork: public Command
{
    const std::string name_ = "work_command";

    Field *field;

    int worker_x;
    int worker_y;

    int target_x;
    int target_y;

    bool ableToWork = 1;

    Team team;

public:
    CmdWork(Field *field, const EntityInterface& worker, int target_x, int target_y);
    bool execute(Logger *logger) override;
    const std::string & name() const override;

    bool valid_p() const;
    Team getTeam() const override;
};

#endif // CMDWORK_H
