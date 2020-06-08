#ifndef CMDUSEITEM_H
#define CMDUSEITEM_H

#include <exception>

#include "game_elements/commands/command.h"

class EntityInterface;
class Field;

class CmdUseItem : public Command
{
    const std::string name_ = "use_item_command";

    Field *field;
    int user_x, user_y;
    int item_x, item_y;

    Team team;

public:


    CmdUseItem(Field *field, const EntityInterface& user, const EntityInterface &item);
    bool execute(Logger *logger) override;
    const std::string & name() const override;

    Team getTeam() const override;
};

#endif // CMDUSEITEM_H
