#include "attack.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::attack::type () const {
    return j_attack::type;
}

void com::attack::serialize_public (const ent::unit& owner, json& package) const {
    package[j_attack::damage] = owner.get_parameter<float>(j_attack::damage);
    package[j_attack::is_attacking] = owner.get_parameter<bool>(j_attack::is_attacking);
}

void com::attack::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_attack::attack_target, -1);
    prototype.set_parameter(j_attack::is_attacking, false);
    prototype.set_parameter(j_attack::damage, (float) 2.0);
}

void com::attack::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {
    //TODO hit back?
}

void com::attack::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    if (input.contains(j_attack_signal::is_attacking)) {
        owner.set_parameter(j_attack::is_attacking, input[j_attack_signal::is_attacking].get<bool>());
    }
    if (input.contains(j_attack_signal::attack_target)) {
        int attack_target = (input[j_attack_signal::attack_target]);
        owner.set_parameter(j_attack::attack_target, attack_target);
    }
}

void com::attack::update (ent::unit& owner, game::abstract_game& context) {
    bool is_attacking = owner.get_parameter<bool>(j_attack::is_attacking);
    if (is_attacking) {
        int attack_target = owner.get_parameter<int>(j_attack::attack_target);
        logger::say() << "\t\t" << "Unit is attacking unit id " << attack_target << logger::over;
        if (context.get_unit(attack_target)) {
            json package;
            package[j_attack::damage] = owner.get_parameter<float>(j_attack::damage);
            context.get_unit(attack_target)->command(owner, context, j_mortal::type, package);
        } else {
            owner.set_parameter<bool>(j_attack::is_attacking, false);
        }
    } else {
        logger::say() << "\t\t" << "Unit is beating around the bush." << logger::over;
    }
}
