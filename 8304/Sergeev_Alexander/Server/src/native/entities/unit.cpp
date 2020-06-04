#include "unit.hpp"
#include "../game/abstract_game.hpp"

ent::unit::unit (unit_prototype* nprototype, int nplayer_id, int nid) {
    prototype = nprototype;
    player_uid = nplayer_id;
    id = nid;
    is_dirty = true;
}

ent::unit::unit (game::abstract_game& context, json& package) {
    parameter_map::deserialize(package);
    if (package.contains(j_unit::prototype)) prototype = context.get_prototype(package[j_unit::prototype]);
    else prototype = nullptr; // TODO optimize
    id = package[j_unit::id].get<int>();
    player_uid = package[j_unit::player_uid].get<int>();
}

void ent::unit::serialize (json& package) const {
    ensure_cache();
    package = cache;
}

void ent::unit::deserialize (json& package) {
    parameter_map::deserialize(package);
    if (package.contains(j_unit::prototype)) prototype = new unit_prototype(package[j_unit::prototype]);
    else prototype = nullptr; // TODO optimize
    id = package[j_unit::id].get<int>();
    player_uid = package[j_unit::player_uid].get<int>();
}

void ent::unit::serialize_public (json& package) const {
    ensure_cache();
    package = cache_public;
}

void ent::unit::set_dirty () {
    is_dirty = true;
}

void ent::unit::set_prototype (unit_prototype* nprototype) {
    delete nprototype; // TODO will crash if prototype was lightweight (use shared_ptr)
    prototype = nprototype;
}

int ent::unit::get_player_id () {
    return player_uid;
}

int ent::unit::get_id () {
    return id;
}

void ent::unit::update (game::abstract_game& context) {
    if (prototype) prototype->update(*this, context); //FIXME
}

void ent::unit::signal (game::abstract_game& context, std::string component_name, json& component_data) {
    if (prototype) prototype->signal(*this, context, component_name, component_data); //FIXME
}

void ent::unit::command (unit& sender, game::abstract_game& context, std::string component_name, json& component_data) {
    if (prototype) prototype->command(sender, *this, context, component_name, component_data); //FIXME
}

void ent::unit::ensure_cache () const {
    if (is_dirty) {
        cache = {};
        cache[j_unit::player_uid] = player_uid;
        cache[j_unit::id] = id;
        cache_public = cache;

        parameter_map::serialize(cache);
        OBSOLETE parameter_map::serialize(cache_public);
        if (prototype) {
            prototype->serialize(cache[j_unit::prototype]);
            OBSOLETE prototype->serialize(cache_public[j_unit::prototype]);
            //prototype->get_cache_public(*this, cache_public); //FIXME
        }
        is_dirty = false;
    }
}









