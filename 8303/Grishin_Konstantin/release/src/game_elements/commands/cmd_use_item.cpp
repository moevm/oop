#include "cmd_use_item.h"

#include "game_elements/interface/entity_interface.h"
#include "game_elements/field.h"
#include "game_elements/team.h"

#include "logger.h"

CmdUseItem::CmdUseItem(Field *field,
                       const EntityInterface &user,
                       const EntityInterface &item):
    field(field),
    user_x(user.getPos().x),
    user_y(user.getPos().y),
    item_x(item.getPos().x),
    item_y(item.getPos().y)
{
    if(user.empty())
        throw empty_interface("empty user", 61);
    if(item.empty())
        throw  empty_interface("empty item", 62);

    team = user.getTeam();
}


bool CmdUseItem::execute(Logger *logger){

    if(logger)
        (*logger) << "unit from ("
                  << std::to_string(user_x) << "; "
                  << std::to_string(user_y) << ") "
                  << "tries to use item on ("
                  << std::to_string(item_x) << "; "
                  << std::to_string(item_y) << ")\n";

    return field->useItem(user_x, user_y, item_x, item_y);
}


const std::string& CmdUseItem::name() const
{
    return name_;
}


Team CmdUseItem::getTeam() const{
    return team;
}
