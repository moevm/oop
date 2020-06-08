#include "game_elements/units/worker_unit_factory.h"

#include "game_elements/units/stats_flyweight.h"
#include "game_elements/units/concrete_units.h"

#include <SFML/System/Vector2.hpp>

WorkerUnitFactory::WorkerUnitFactory(Team team):
    team(team)
{}


Worker* WorkerUnitFactory::createWorker(int x_pos, int y_pos){
    auto& stats_lib = StatsFlyweight::getInstance();
    auto& stats = stats_lib.createStats(8, 3);
    return new Worker(team, sf::Vector2i(x_pos, y_pos), stats);
}
