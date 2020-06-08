#ifndef CMDATTACK_H
#define CMDATTACK_H

#include "game_elements/commands/command.h"

class Field;

class CmdAttack : public Command
{
    const std::string name_ = "attack_command";

    Field *field;
    int from_x, from_y;
    int to_x, to_y;

    Team team;

    bool ableToAttack = 1;

public:
    CmdAttack(Field *field, const EntityInterface& attacking, int to_x, int to_y);
    bool execute(Logger *logger) override;
    const std::string & name() const override;
    bool valid_p() const;

    Team getTeam() const override;
};

#endif // CMDATTACK_H
