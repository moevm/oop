#include "cmd_work.h"

#include "game_elements/interface/entity_interface.h"
#include "game_elements/field.h"

#include "logger.h"

CmdWork::CmdWork(Field *field, const EntityInterface& worker, int target_x, int target_y):
    field(field), worker_x(worker.getPos().x),
    worker_y(worker.getPos().y),
    target_x(target_x), target_y(target_y)
{
    team = worker.getTeam();
    for(auto &pos: worker.getTargets()){
        if(pos == sf::Vector2i(target_x, target_y))
            return;
    }

    if(worker.empty())
        throw empty_interface("non-existent worker unit", 71);

    if(field->getCell(target_x, target_y).empty())
        throw CellInterface::empty_cell("try to attack non-existen cell", 71);

    ableToWork = 0;
}


bool CmdWork::execute(Logger *logger){
    if(!ableToWork){
        if(logger)
            (*logger) << "cell out of work range\n";
        return 0;
    }

    if(logger)
        (*logger) << "worker on ("
                  << std::to_string(worker_x) << "; "
                  << std::to_string(worker_y) << ") "
                  << "tries to treat ("
                  << std::to_string(target_x) << "; "
                  << std::to_string(target_y) << ") cell\n";

    return field->work(worker_x, worker_y, target_x, target_y);
}


const std::string& CmdWork::name() const
{
    return name_;
}


bool CmdWork::valid_p() const{
    return ableToWork;
}


Team CmdWork::getTeam() const{
    return team;
}
