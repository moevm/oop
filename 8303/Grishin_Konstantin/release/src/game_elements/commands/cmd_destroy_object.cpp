#include "cmd_destroy_object.h"

#include "game_elements/field.h"
#include "game_elements/interface/entity_interface.h"
#include "game_elements/team.h"

#include "logger.h"

CmdDestroyObject::CmdDestroyObject(Field *field,
                                   const EntityInterface& user,
                                   const EntityInterface &item):
    field(field),
    user_x(user.getPos().x),
    user_y(user.getPos().y),
    item_x(item.getPos().x),
    item_y(item.getPos().y)
{
    if(item.empty())
        throw empty_interface("can't destroy non_existent item", 41);
    team = user.getTeam();
}


bool CmdDestroyObject::execute(Logger *logger){
    if(logger)
        (*logger) << "try to destroy object on ("
                  << std::to_string(item_x) << "; "
                  << std::to_string(item_y) << ")\n";

    return field->destroyItem(item_x, item_y);
}


const std::string& CmdDestroyObject::name() const
{
    return name_;
}


Team CmdDestroyObject::getTeam() const{
    return team;
}
