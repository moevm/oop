#include "storage.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::storage::type () const {
    return j_storage::type;
}

void com::storage::serialize_public (const ent::unit& owner, json& package) const { }

void com::storage::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_storage::unload, false);
    prototype.set_parameter(j_storage::garrison, stts::vector2<int>(-1, -1));
}

void com::storage::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {
    if (sender.get_player_id() != owner.get_player_id()) {
        input[j_storage::stored] = false;
        return;
    }
    stts::vector2<int> garrison = owner.get_parameter<stts::vector2<int>>(j_storage::garrison);
    if (garrison.x == -1) {
        garrison.x = sender.get_id();
        input[j_storage::stored] = true;
    } else if (garrison.y == -1) {
        garrison.y = sender.get_id();
        input[j_storage::stored] = true;
    } else {
        input[j_storage::stored] = false;
    }
}

void com::storage::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    if (input.contains(j_storage_signal::unload)) {
        owner.set_parameter(j_storage::unload, input[j_storage_signal::unload].get<bool>());
    }
}

void com::storage::update (ent::unit& owner, game::abstract_game& context) {
    bool unload = owner.get_parameter<bool>(j_storage::unload);
    stts::vector2<int> garrison = owner.get_parameter<stts::vector2<int>>(j_storage::garrison);
    if (unload && garrison.is_set()) {
        int id = garrison.x == -1 ? garrison.x : garrison.y;
        stts::vector2<int> pos = owner.get_parameter<stts::vector2<int>>(j_locationable::position);
        std::vector<stts::vector2<int>> nei = context.get_tilemap().get_neighbours(pos);
        for (int i = 0; i < (int) nei.size(); ++i)
            if (!context.get_tilemap().get_tile(nei[i]).is_occupied()) {
                json package;
                nei[i].serialize(package[j_locationable::position]);
                context.get_unit(id)->command(owner, context, j_locationable::type, package);
                if (garrison.x == id) garrison.x = -1;
                else garrison.y = -1;
                break;
            }
        owner.set_parameter<bool>(j_storage::unload, false);
        owner.set_parameter<stts::vector2<int>>(j_storage::garrison, garrison);
    }
}








