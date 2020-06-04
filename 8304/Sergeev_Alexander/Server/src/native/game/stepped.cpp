#include "stepped.hpp"

game::stepped::stepped () : abstract_game() { }

game::stepped::stepped (json& package) {
    stepped::deserialize(package);
}

const std::string& game::stepped::type () const {
    return j_stepped::type;
}

void game::stepped::serialize_concrete_player (int player_uid, json& package) {
    package[j_typed::type] = j_stepped::type;
    // TODO
}

void game::stepped::update (json& output) {
    // TODO
}




