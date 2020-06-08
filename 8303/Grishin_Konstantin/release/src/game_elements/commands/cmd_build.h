#ifndef CMDBUILD_H
#define CMDBUILD_H

#include "game_elements/commands/command.h"

class Field;
class CellInterface;
enum class Team;

class CmdBuild : public Command
{
    const std::string name_ = "build_command";

    Team team;
    Field *field;

    int x, y;
    int type;
    int rot;

    int score = 0;

public:
    CmdBuild(Team team, Field* field, int x, int y, int b_type, int rot);
    bool execute(Logger *logger) override;
    const std::string & name() const override;

    Team getTeam() const override;
    int getScore() const override;
};

#endif // CMDBUILD_H
