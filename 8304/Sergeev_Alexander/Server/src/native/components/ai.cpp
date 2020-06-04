#include "ai.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::ai::type () const {
    return j_ai::type;
}

void com::ai::serialize_public (const ent::unit& owner, json& output) const {
    output[j_ai::is_online] = owner.get_parameter<bool>(j_ai::is_online);
}

void com::ai::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_ai::is_online, true);
}

void com::ai::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) { }

void com::ai::signal (ent::unit& owner, game::abstract_game& context, json& input) { }

void com::ai::update (ent::unit& owner, game::abstract_game& context) { }
