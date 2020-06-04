#include "ai_walker.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::ai_walker::type () const {
    return j_ai_walker::type;
}

void com::ai_walker::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) { }

void com::ai_walker::update (ent::unit& owner, game::abstract_game& context) {
    bool is_moving = owner.get_parameter<bool>(j_move::is_moving);
    bool is_online = owner.get_parameter<bool>(j_ai::is_online);
    if (!is_moving && is_online) {
        srand(owner.get_id());
        stts::vector2<int> move_target(rand() % context.get_tilemap().get_scale().x, rand() % context.get_tilemap().get_scale().y);
        owner.set_parameter<stts::vector2<int>>(j_move::move_target, move_target);
        owner.set_parameter<bool>(j_move::is_moving, true);
    }
}
