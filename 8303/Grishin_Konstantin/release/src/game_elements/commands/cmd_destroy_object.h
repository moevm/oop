#ifndef CMDDESTROYOBJECT_H
#define CMDDESTROYOBJECT_H

#include "game_elements/commands/command.h"

class Field;
class EntityInterface;

class CmdDestroyObject : public Command
{
    const std::string name_ = "destroy_object_command";

    Field *field;
    int user_x, user_y;
    int item_x, item_y;

    Team team;

public:
    CmdDestroyObject(Field *field, const EntityInterface& user, const EntityInterface &item);
    bool execute(Logger *logger) override;
    const std::string & name() const override;

    Team getTeam() const override;
};

#endif // CMDDESTROYOBJECT_H
