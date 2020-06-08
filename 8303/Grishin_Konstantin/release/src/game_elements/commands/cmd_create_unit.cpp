#include "cmd_create_unit.h"

#include "game_elements/field.h"
#include "game_elements/team.h"
#include "game_elements/units/unit.h"
#include "game_elements/buildings/building.h"

#include "logger.h"


CmdCreateUnit::CmdCreateUnit(EntityInterface& creator, Field *field, Unit::Type type):
    creator(creator), field(field), type(type)
{
    team = creator.getTeam();
    if(creator.empty()){
        throw Command::empty_interface("non-existent creator", 41);
    }
    if(creator.getEntityType() != Entity::Building){
        throw Entity::wrong_type("Can't create unit from non-building", 41);
    }
}


bool CmdCreateUnit::execute(Logger *logger){
    if(type == Unit::Melee)
        score = -2;
    if(type == Unit::Range)
        score = -4;
    if(type == Unit::Nuker)
        score = -6;
    if(type == Unit::Worker)
        score = -1;

    if(logger){
        std::string creator_name;
        if(team == Team::Blu)
            creator_name = "blu ";
        if(team == Team::Red)
            creator_name = "red ";
        if(team == Team::Neutral)
            creator_name = "neutral";

        if(creator.getID() == "building_base")
            creator_name += "base";
        if(creator.getID() == "building_tower")
            creator_name += "tower";
        if(creator.getID() == "building_barrack")
            creator_name += "barrack";

        std::string unit_name;
        if(type == Unit::Melee)
            unit_name = "melee unit";
        if(type == Unit::Range)
            unit_name = "range unit";
        if(type == Unit::Nuker)
            unit_name = "nuker unit";
        if(type == Unit::Worker)
            unit_name = "worker unit";

        (*logger) << creator_name << " tries to create " << unit_name
                  << " from position ("
                  << std::to_string(creator.getPos().x) << "; "
                  << std::to_string(creator.getPos().y) << ")\n";
    }

    return field->createUnit(creator.getPos().x, creator.getPos().y, type);
}


const std::string& CmdCreateUnit::name() const
{
    return name_;
}


Team CmdCreateUnit::getTeam() const{
    return team;
}


int CmdCreateUnit::getScore() const{
    return score;
}
