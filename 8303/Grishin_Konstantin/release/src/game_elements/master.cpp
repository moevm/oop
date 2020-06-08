#include "master.h"

#include "game_elements/field.h"
#include "game_elements/entity.h"
#include "game_elements/cell.h"

#include "game_elements/cell_grid.h"
#include "game_elements/entity_container.h"

#include "game_elements/units/concrete_units/worker.h"
#include "game_elements/neutral_objects/object.h"
#include <iostream>

#include "logger.h"

Master::Master(Field *field):
    field(field)
{}


std::pair<int, int> Master::checkEntities(Logger *logger){

    int red = 0;
    int blu = 0;

    if(logger)
        (*logger) << "\t\tmaster:\n";

    for(size_t i = 0; i < field->entities->size(); i++){
        auto entity = field->entities->at(i);
        if(auto u = dynamic_cast<Unit*>(entity))
        {
            u->resetSteps();
        }

        if(auto w = dynamic_cast<Worker*>(entity)){
            auto action = w->action();
            if(action.workAction.work){
                auto target_cell = field->grid->getCell(action.workAction.x,
                                                        action.workAction.y);
                auto target = target_cell->getEntity();
                if(auto t = dynamic_cast<Object*>(target)){
                    std::string team;
                    if(w->getTeam() == Team::Red) team = "red";
                    else team = "blu";

                    if(logger){
                        (*logger) << "\t\t" << team << " worker on ("
                                  << std::to_string(w->getPosition().x) << "; "
                                  << std::to_string(w->getPosition().y) << ") "
                                  << " treats object on ("
                                  << std::to_string(t->getPosition().x) << "; "
                                  << std::to_string(t->getPosition().y) << ")\n";
                    }

                    auto inheritor = t->treat();

                    target_cell->pullEntity();
                    target_cell->setEntity(inheritor);

                    if(inheritor != t){
                        if(logger)
                            (*logger) << "\t\tobject treated\n";

                        if(w->getTeam() == Team::Red){
                            red += t->getScore();
                        } else if (w->getTeam() == Team::Blu){
                            blu += t->getScore();
                        }

                        w->setActionState();
                        if(inheritor != nullptr)
                            field->entities->push_back(inheritor);
                    } else {
                        if(logger)
                            (*logger) << "\t\tobject not treated, continue to work\n";
                    }

                }
            }
        }
    }

    for(size_t i = 0; i < field->entities->size(); i++){
        auto entity = field->entities->at(i);
        if(entity->delete_p()){
            if(logger)
                (*logger) << "\t\t" << entity->getID() << " is gone\n";

            if(entity->getEntityType() == Entity::Unit){
                if(entity->getID() == "unit_knight")
                {
                    if(entity->getTeam() == Team::Red) blu += 3;
                    else red += 3;
                }

                else if(entity->getID() == "unit_troll")
                {
                    if(entity->getTeam() == Team::Red) blu += 4;
                    else red += 4;
                }

                else if(entity->getID() == "unit_arhcer")
                {
                    if(entity->getTeam() == Team::Red) blu += 3;
                    else red += 3;
                }

                else if (entity->getID() == "unit_atrons")
                {
                    if(entity->getTeam() == Team::Red) blu += 5;
                    else red += 5;
                }

                else if (entity->getID() == "unit_berserk")
                {
                    if(entity->getTeam() == Team::Red) blu += 4;
                    else red += 4;
                }

                else if (entity->getID() == "unit_wizard")
                {
                    if(entity->getTeam() == Team::Red) blu += 6;
                    else red += 6;
                }

                else if (entity->getID() == "unit_worker")
                {
                    if(entity->getTeam() == Team::Red) blu += 1;
                    else red += 1;
                }
            }

            if(entity->getID() == "building_base"){
                if(entity->getTeam() == Team::Red)
                    field->redBase = nullptr;
                else
                    field->bluBase = nullptr;
            }

            field->entities->remove(entity);
            i--;

            auto cell = field->grid->getCell(entity->getPosition().x, entity->getPosition().y);
            if(cell->getEntity() == entity)
                cell->pullEntity();

            delete entity;
        }
    }

    if(logger)
        (*logger) << "\t\tmaster finished\n";

    return std::pair<int, int>(red, blu);
}
