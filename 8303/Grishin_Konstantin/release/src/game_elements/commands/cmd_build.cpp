#include "cmd_build.h"

#include "game_elements/field.h"
#include "game_elements/team.h"
#include "game_elements/buildings/building.h"

#include "logger.h"

CmdBuild::CmdBuild(Team team, Field* field, int x, int y, int b_type, int rot):
    team(team), field(field), x(x), y(y), type(b_type), rot(rot)
{
    if(field->getCell(x, y).empty())
        throw CellInterface::empty_cell("non-existent cell", 21);
}


bool CmdBuild::execute(Logger *logger){
    if(type == Building::Tower)
        score = -10;
    if(type == Building::Barrack)
        score = -6;


    if(logger){
        std::string building_name;
        if(team == Team::Red)
            building_name = "red ";
        if(team == Team::Blu)
            building_name = "blu ";
        if(team == Team::Neutral)
            building_name = "neutral ";

        if(type == Building::Base)
            building_name += "base";
        if(type == Building::Tower)
            building_name += "tower";
        if(type == Building::Barrack)
            building_name += "barrack";

        (*logger) << "try to build " << building_name << " on position ("
                  << std::to_string(x) << "; "
                  << std::to_string(y) << "\n";
    }

    bool good = field->createBuilding(team, type, x, y, rot);
    return good;
}


const std::string& CmdBuild::name() const
{
    return name_;
}


Team CmdBuild::getTeam() const{
    return team;
}


int CmdBuild::getScore() const{
    return score;
}
