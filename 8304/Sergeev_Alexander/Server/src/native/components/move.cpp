#include "move.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::move::type () const {
    return j_move::type;
}

void com::move::serialize_public (const ent::unit& owner, json& output) const {
    output[j_move::is_moving] = owner.get_parameter<bool>(j_move::is_moving);
    // TODO p_position (float) and p_tile_position (int)
}

void com::move::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_move::is_moving, false);
    prototype.set_parameter(j_move::is_stopped, false);
    prototype.set_parameter(j_move::move_target, stts::vector2<int>(-1, -1));
    prototype.set_parameter(j_move::move_path, std::list<stts::vector2<int>>());
}

void com::move::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) {
    throw unimplemented_exception("com::move::command was not implemented");
}

void com::move::signal (ent::unit& owner, game::abstract_game& context, json& input) {
    if (input.contains(j_move_signal::is_moving)) {
        owner.set_parameter(j_move::is_moving, input[j_move_signal::is_moving].get<bool>());
    }
    if (input.contains(j_move_signal::move_target)) {
        stts::vector2<int> move_target = stts::vector2<int>(input[j_move_signal::move_target]);
        owner.set_parameter(j_move::move_target, move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(j_locationable::position);
        std::list<stts::vector2<int>> target = context.get_tilemap().get_path(position, move_target);
        owner.set_parameter(j_move::move_path, target);
    }
}

void com::move::update (ent::unit& owner, game::abstract_game& context) {
    bool is_moving = owner.get_parameter<bool>(j_move::is_moving);
    bool is_stopped = owner.get_parameter<bool>(j_move::is_stopped);
    if (is_moving && !is_stopped) {
        stts::vector2<int> move_target = owner.get_parameter<stts::vector2<int>>(j_move::move_target);
        stts::vector2<int> position = owner.get_parameter<stts::vector2<int>>(j_locationable::position);

        logger::say() << "\t\t" << "Unit is moving to (" << move_target.x << ", " << move_target.y << ")." << logger::over;

        if (context.get_tilemap().get_distance(position, move_target) <= 1) { // TODO normal float distance and parameters
            owner.set_parameter<bool>(j_move::is_moving, false);
            context.get_tilemap()[position].on_unit_enter(owner);
        } else {
            // TODO is it fast enough?
            std::list<stts::vector2<int>> path = owner.get_parameter<std::list<stts::vector2<int>>>(j_move::move_path);
            if (path.empty()) {
                owner.set_parameter<bool>(j_move::is_moving, false);
                context.get_tilemap()[position].on_unit_enter(owner);
                logger::say() << "\t\t" << "Path blocked!" << logger::over;
                // TODO check if occupied then find another tile without units
            } else {
                stts::vector2<int> next_position = path.back();
                logger::say() << "\t\t" << "Next position (" << next_position.x << ", " << next_position.y << ")." << logger::over;
                tile::base_tile& nt = context.get_tilemap()[next_position];

                if (!nt.is_occupied()) {
                    path.pop_back();
                    owner.set_parameter<std::list<stts::vector2<int>>>(j_move::move_path, path);

                    logger::say() << "\t\t" << "Entering tile..." << logger::over;
                    nt.on_unit_enter(owner);
                    tile::base_tile &t = context.get_tilemap()[position];
                    if (t.get_occupier_id() == owner.get_id()) t.on_unit_exit(owner);

                    owner.set_parameter(j_locationable::position, next_position);
                } else {
                    logger::say() << "\t\t" << "Tile occupied, addressing occupier..." << logger::over;
                    json j;
                    context.get_unit(nt.get_occupier_id())->command(owner, context, j_storage::type, j);
                    if ((j.contains(j_storage::stored)) && (j[j_storage::stored].get<bool>() == true)) {
                        tile::base_tile& t = context.get_tilemap()[owner.get_parameter<stts::vector2<int>>(j_locationable::position)];
                        if (t.get_occupier_id() == owner.get_id()) t.on_unit_exit(owner);
                        owner.set_parameter(j_locationable::position, stts::vector2<int>(-1, -1));
                    }
                }
            }
        }
    } else {
        logger::say() << "\t\t" << "Unit stopped or not moving" << logger::over;
    }
}
