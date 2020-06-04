#include "ai_attacker.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::ai_attacker::type () const {
    return j_ai_attacker::type;
}

void com::ai_attacker::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) { }

void com::ai_attacker::update (ent::unit& owner, game::abstract_game& context) {
    bool is_attacking = owner.get_parameter<bool>(j_attack::is_attacking);
    bool is_online = owner.get_parameter<bool>(j_ai::is_online);
    if (!is_attacking && is_online) {
        srand(owner.get_id());
        int attack_target = rand() % context.get_units_count();
        owner.set_parameter<int>(j_attack::attack_target, attack_target);
        owner.set_parameter<bool>(j_attack::is_attacking, true);
    }
}
