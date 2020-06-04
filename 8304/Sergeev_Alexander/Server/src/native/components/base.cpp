#include "base.hpp"
#include "../entities/unit.hpp"
#include "../game/abstract_game.hpp"

const std::string& com::base::type () const {
    return j_base::type;
}

void com::base::serialize_public (const ent::unit& owner, json& output) const {
    output[j_base::is_defeated] = owner.get_parameter<bool>(j_base::is_defeated);
}

void com::base::setup_prototype (ent::unit_prototype& prototype) {
    prototype.set_parameter(j_base::defenders_tikz, 0);
    prototype.set_parameter(j_base::is_defeated, false);
}

void com::base::command (ent::unit& sender, ent::unit& owner, game::abstract_game& context, json& input) { }

void com::base::signal (ent::unit& owner, game::abstract_game& context, json& input) { }

void com::base::update (ent::unit& owner, game::abstract_game& context) {
    bool is_defeated = owner.get_parameter<bool>(j_base::is_defeated);
    int defenders_tikz = owner.get_parameter<int>(j_base::defenders_tikz);
    if ((defenders_tikz > 0) || (is_defeated)) {
        logger::say() << "\t\t" << "Defender will be ready in " << 5 - defenders_tikz << " updates." << logger::over;
        if (defenders_tikz == 5) {
            stts::vector2<int> pos = owner.get_parameter<stts::vector2<int>>(j_locationable::position);
            std::vector<stts::vector2<int>> nei = context.get_tilemap().get_neighbours(pos);
            for (int i = 0; i < (int) nei.size(); ++i)
                if (!context.get_tilemap().get_tile(nei[i]).is_occupied()) {
                    logger::say() << "\t\t" << "Spawned defender (solemn) to (" << nei[i].x << ", " << nei[i].y << ")." << logger::over;
                    context.get_tilemap().transpose(context.make_unit("solemn", owner.get_player_id()), nei[i]);
                    break;
                }
            owner.set_parameter<int>(j_base::defenders_tikz, 0);
            owner.set_parameter<bool>(j_base::is_defeated, false);
        } else {
            owner.set_parameter<int>(j_base::defenders_tikz, defenders_tikz + 1);
        }
    }
    if (!is_defeated) {
        int units = 0;
        for (int i = 1; i <= context.get_units_count(); ++i) {
            if (context.get_unit(i))
                if (context.get_unit(i)->get_player_id() == owner.get_player_id()) units++;
        }
        owner.set_parameter<bool>(j_base::is_defeated, units < 2);
        if (units < 2) logger::say() << "\t\t" << "Alert! Only base left! Starting generating defender!" << logger::over;
        else logger::say() << "\t\t" << "No alert, we still have " << units << " units left." << logger::over;
    }
}
