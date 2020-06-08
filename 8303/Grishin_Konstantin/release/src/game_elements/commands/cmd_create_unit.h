#ifndef CMDCREATEUNIT_H
#define CMDCREATEUNIT_H

#include <string>
#include "game_elements/commands/command.h"
#include "game_elements/units/unit.h"

class Field;
class EntityInterface;
class Building;


class CmdCreateUnit : public Command
{
    const std::string name_ = "create_unit_command";

    EntityInterface &creator;
    Field *field;
    Unit::Type type;

    Team team;
    int score = 0;

public:
    CmdCreateUnit(EntityInterface& creator, Field *field, Unit::Type type);
    bool execute(Logger *logger) override;
    const std::string & name() const override;

    Team getTeam() const override;
    int getScore() const override;
};

#endif // CMDCREATEUNIT_H
