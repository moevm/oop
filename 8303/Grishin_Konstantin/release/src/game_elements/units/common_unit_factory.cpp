#include "common_unit_factory.h"

#include "game_elements/units/concrete_units.h"
#include "game_elements/units/stats_flyweight.h"

#include <SFML/System/Vector2.hpp>

CommonUnitFactory::CommonUnitFactory(Team team):
    BattleUnitFactory(team)
{}


Melee* CommonUnitFactory::createMelee(int x_pos, int y_pos)
{
    auto& stats_lib = StatsFlyweight::getInstance();
    auto& stats = stats_lib.createStats(30, 3, 5);
    return new Knight(team, sf::Vector2i(x_pos, y_pos), stats);
}


Range* CommonUnitFactory::createRange(int x_pos, int y_pos)
{
    auto& stats_lib = StatsFlyweight::getInstance();
    auto& stats = stats_lib.createStats(20, 2, 5, 3, 1);
    return new Archer(team, sf::Vector2i(x_pos, y_pos), stats);
}


Nuker* CommonUnitFactory::createNuker(int x_pos, int y_pos)
{
    auto& stats_lib = StatsFlyweight::getInstance();
    auto& stats = stats_lib.createStats(20, 1, 5, 1);
    return new Berserk(team, sf::Vector2i(x_pos, y_pos), stats);
}
