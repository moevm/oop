#include "cmd_move.h"

#include "game_elements/field.h"

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "game_elements/team.h"

#include "logger.h"

CmdMove::CmdMove(Field *field, EntityInterface &entity, int to_x, int to_y):
    field(field), entity(entity), x(to_x), y(to_y)
{
    team = entity.getTeam();

    if(field->getCell(x, y).empty()){
        throw CellInterface::empty_cell("try to move to empty cell", 51);
    }

    if(entity.empty())
        throw empty_interface("can't move non-existent unit", 51);

    for(auto &p: entity.getWays()){
        if (p.first == sf::Vector2i(to_x, to_y))
        {
            residualSteps = p.second;
            return;
        }
    }

    ableToMove = 0;
}


bool CmdMove::execute(Logger *logger){
    if(!ableToMove){
        if(logger)
            (*logger) << "cell out of move range\n";
        return 0;
    }

    if(logger)
        (*logger) << "try to move entity from ("
                  << std::to_string(entity.getPos().x) << "; "
                  << std::to_string(entity.getPos().y) << ") to ("
                  << std::to_string(x) << "; "
                  << std::to_string(y) << ")\n";

    bool moved_correctly = field->moveUnit(entity.getPos().x, entity.getPos().y, x, y, residualSteps);
    return moved_correctly;
}


const std::string& CmdMove::name() const
{
    return name_;
}


bool CmdMove::valid_p() const{
    return ableToMove;
}


Team CmdMove::getTeam() const{
    return team;
}
