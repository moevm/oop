#include "simple.hpp"
#include "../game/realtime.hpp"
#include "../tilemap/square.hpp"
#include "../rules/skirmish.hpp"

generators::simple::simple (int nseed, std::set<int> nplayers_uid, const stts::vector2<int>& ntilemap_scale) {
    seed = nseed;
    players_uid = nplayers_uid;
    tilemap_scale = ntilemap_scale;
}

generators::simple::simple (json& package) {
    simple::deserialize(package);
}

void generators::simple::serialize (json& package) const {
    abstract_generator::serialize(package);
    package[j_simple::seed] = seed;
    package[j_simple::players_uid] = players_uid;
    tilemap_scale.serialize(package[j_simple::tilemap_scale]);
}

void generators::simple::deserialize (json& package) {
    abstract_generator::deserialize(package);
    try {
        seed = package[j_simple::seed];
    } catch (std::exception& e) {
        seed = 42;
    }
    tilemap_scale = stts::vector2<int>(package[j_simple::tilemap_scale]);
    if (tilemap_scale.x < 0) tilemap_scale.x = -tilemap_scale.x;
    if (tilemap_scale.x == 0) tilemap_scale.x = 10;
    if (tilemap_scale.y < 0) tilemap_scale.y = -tilemap_scale.y;
    if (tilemap_scale.y == 0) tilemap_scale.y = 10;
}

const std::string& generators::simple::type () const {
    return j_simple::type;
}

std::unique_ptr<game::abstract_game> generators::simple::generate () {
    srand(seed);
    std::unique_ptr<game::abstract_game> game = std::make_unique<game::realtime>();

    // Tilemap
    std::unique_ptr<tilemap::abstract_tilemap> tilemap = std::make_unique<tilemap::square>(tilemap_scale);
    game->set_tilemap(std::move(tilemap));
    for (int ny = 0; ny < tilemap_scale.y; ny++) {
        for (int nx = 0; nx < tilemap_scale.x; nx++) {
            int per_seed = rand();
            int tile_seed = (abs(per_seed * nx * ny)) % 10;
            float height = (float) ((per_seed % 200) - 100) / 100;

            tile::base_tile* tile;
            if (tile_seed % 5 == 0) {
                tile = new tile::damage_dealer(height);
            } else if (tile_seed % 3 == 0) {
                tile = new tile::money_dealer(height);
            } else {
                tile = new tile::base_tile(height);
            }
            game->get_tilemap().set_tile(nx, ny, tile);
        }
    }
    game->set_rule(std::make_unique<rules::skirmish>());

    // Factory
    ent::unit_prototype* base = new ent::unit_prototype("base");
    base->add_component(com::j_locationable::type);
    base->add_component(com::j_mortal::type);
    base->add_component(com::j_spawner::type);
    base->add_component(com::j_storage::type);
    base->add_component(com::j_base::type);
    game->set_prototype(base);

    ent::unit_prototype* solemn = new ent::unit_prototype("solemn");
    solemn->add_component(com::j_locationable::type);
    solemn->add_component(com::j_move::type);
    solemn->add_component(com::j_mortal::type);
    solemn->add_component(com::j_attack::type);
    game->set_prototype(solemn);


    // Players
    for (auto i : players_uid) {
        logger::say() << "" << "Making player id " << i << logger::over;
        stts::player *player = new stts::player(i);
        player->set(stts::player_params::money, seed % 400 + 100);
        game->set_player(i, player);

        stts::vector2<int> spawn = mathematics::circle_set(tilemap_scale, i, players_uid.size());
        int radius = tilemap_scale.x / 16;

        float middle_height = 0.0;
        double square = radius*radius*4.0;
        for (int j = spawn.y - radius; j < spawn.y + radius; ++j) {
            for (int k = spawn.x - radius; k < spawn.y + radius; ++k) {
                middle_height += game->get_tilemap().get_tile(k, j).get_height();
            }
        }

        middle_height /= (float) square;

        for (int j = spawn.y - radius; j < spawn.y + radius; ++j) {
            for (int k = spawn.x - radius; k < spawn.y + radius; ++k) {
                 game->get_tilemap().get_tile(k, j).set_height(middle_height);
            }
        }

        stts::vector2<int> unit1_offset(-radius/2, 0), unit2_offset(radius/2, 0);

        // Base
        ent::unit &u_base = game->make_unit("base", i);
        game->get_tilemap().transpose(u_base, spawn + stts::vector2<int>(radius / 2, 0));
        logger::say() << "\t" << "Spawned base to (" << (spawn + stts::vector2<int>(radius / 2, 0)).x << ", " << (spawn + stts::vector2<int>(radius / 2, 0)).y << ")." << logger::over;

        // Units
        ent::unit &u_runner_1 = game->make_unit("solemn", i);
        game->get_tilemap().transpose(u_runner_1, spawn + stts::vector2<int>(-radius/2, 0));
        logger::say() << "\t" << "Spawned solemn to (" << (spawn + stts::vector2<int>(-radius/2, 0)).x << ", " << (spawn + stts::vector2<int>(-radius/2, 0)).y << ")." << logger::over;

        /*if (unit1_offset != unit2_offset) { // TODO: remove this to test on SANE-SIZED maps
            ent::unit &u_runner_2 = game->make_unit("solemn", i);
            game->get_tilemap().transpose(u_runner_2, spawn + stts::vector2<int>(radius / 2, 0));
        }*/
    }

    return std::move(game);
}
