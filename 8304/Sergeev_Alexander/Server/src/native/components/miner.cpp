#include "miner.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::miner::type () const {
    return j_miner::type;
}

void com::miner::serialize_public (const ent::unit& owner, json& output) const {
    // TODO p_position (float) and p_tile_position (int)
}

void com::miner::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_miner::is_mining, false);
    prototype.set_parameter(j_miner::is_stopped, false);
    prototype.set_parameter(j_miner::mining_tikz, 0);
}

void com::miner::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {
    if (&sender == &owner) { // Command sent from tile
        int money;
        context.get_player(owner.get_player_id()).get(stts::player_params::money, money);
        money += input[tile::j_money_dealer::money].get<int>();
        context.get_player(owner.get_player_id()).set(stts::player_params::money, money);
    }
}

void com::miner::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    if (input.contains(j_miner_signal::is_mining)) {
        owner.set_parameter(j_miner::is_mining, input[j_miner_signal::is_mining].get<bool>());
    }
}

void com::miner::update (ent::unit& owner, game::abstract_game& context) {
    bool is_mining = owner.get_parameter<bool>(j_miner::is_mining);
    bool is_stopped = owner.get_parameter<bool>(j_miner::is_stopped);
    if (is_mining) {
        if (!is_stopped) owner.set_parameter<bool>(j_miner::is_stopped, true);
        int tikz = owner.get_parameter<bool>(j_miner::mining_tikz);
        if (tikz == 10) {
            int money;
            context.get_player(owner.get_player_id()).get(stts::player_params::money, money);
            money += 5;
            context.get_player(owner.get_player_id()).set(stts::player_params::money, money);
            tikz = 0;
        } else tikz++;
        owner.set_parameter<bool>(j_miner::mining_tikz, tikz);
    } else if (is_stopped) owner.set_parameter<bool>(j_miner::is_stopped, false);
}

