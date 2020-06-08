#include "magic_unit_factory.h"

#include "game_elements/units/concrete_units.h"
#include "game_elements/units/stats_flyweight.h"

#include <SFML/System/Vector2.hpp>

MagicUnitFactory::MagicUnitFactory(Team team):
    BattleUnitFactory(team)
{}


Melee* MagicUnitFactory::createMelee(int x_pos, int y_pos)
{
    auto& stats_lib = StatsFlyweight::getInstance();
    auto& stats = stats_lib.createStats(30, 4, 7);
    return new Troll(team, sf::Vector2i(x_pos, y_pos), stats);
}


Range* MagicUnitFactory::createRange(int x_pos, int y_pos)
{
    auto& stats_lib = StatsFlyweight::getInstance();
    auto& stats = stats_lib.createStats(15, 4, 10, 2, 0);
    return new Atrons(team, sf::Vector2i(x_pos, y_pos), stats);
}


Nuker* MagicUnitFactory::createNuker(int x_pos, int y_pos)
{
    auto& stats_lib = StatsFlyweight::getInstance();
    auto& stats = stats_lib.createStats(15, 2, 8, 2, 0);
    return new Wizard(team, sf::Vector2i(x_pos, y_pos), stats);
}
