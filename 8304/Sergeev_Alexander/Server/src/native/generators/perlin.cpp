#include "perlin.hpp"

#include "../utils/perlin_noise_so.hpp"
#include "../game/realtime.hpp"
#include "../tilemap/square.hpp"
#include "../rules/skirmish.hpp"

generators::perlin::perlin (int nseed, int noctaves, float npersistance, std::set<int> nplayers_uid, const stts::vector2<int>& ntilemap_scale) {
    seed = nseed;
    octaves = noctaves;
    persistance = npersistance;
    players_uid = std::move(nplayers_uid);
    tilemap_scale = ntilemap_scale;
}

generators::perlin::perlin (json& package) {
    perlin::deserialize(package);
}

void generators::perlin::serialize (json& package) const {
    abstract_generator::serialize(package);
    package[j_perlin::seed] = seed;
    package[j_perlin::octaves] = octaves;
    package[j_perlin::persistance] = persistance;
    package[j_perlin::players_uid] = players_uid;
    tilemap_scale.serialize(package[j_perlin::tilemap_scale]);
}

void generators::perlin::deserialize (json& package) {
    abstract_generator::deserialize(package);
    seed = package[j_perlin::seed].get<int>();
    octaves = package[j_perlin::octaves].get<int>();
    persistance = package[j_perlin::persistance].get<float>();
    players_uid = package[j_perlin::players_uid].get<std::set<int>>();
    tilemap_scale = stts::vector2<int>(package[j_perlin::tilemap_scale]);
}

const std::string& generators::perlin::type () const {
    return j_perlin::type;
}

std::unique_ptr<game::abstract_game> generators::perlin::generate () {
    srand(seed);
    std::unique_ptr<game::abstract_game> game = std::make_unique<game::realtime>();

    // Tilemap
    std::unique_ptr<tilemap::abstract_tilemap> tilemap = std::make_unique<tilemap::square>(tilemap_scale);
    game->set_tilemap(std::move(tilemap));
    for (int ny = 0; ny < tilemap_scale.y; ny++) {
        for (int nx = 0; nx < tilemap_scale.x; nx++) {
            float height = perlin_so::ValueNoise_2D(nx, ny, octaves, persistance);
            tile::base_tile* tile = nullptr;
            if (height > 0.9) tile = new tile::damage_dealer(height);
            else if (height < 0.1) tile = new tile::money_dealer(height);
            else tile = new tile::base_tile(height);
            game->get_tilemap().set_tile(nx, ny, tile);
        }
    }
    game->set_rule(std::make_unique<rules::skirmish>());

    // TODO
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
    // TODO

    // Players
    for (auto i : players_uid) {
        stts::player* player = new stts::player(i);
        player->set(stts::player_params::money, seed % 400 + 100);
        game->set_player(i, player);

        stts::vector2<int> spawn = mathematics::circle_set(tilemap_scale, i, players_uid.size());
        int radius = tilemap_scale.x / 16;

        // float middle_height = 0.0;
        // double square = radius * radius * 4.0;
        // for (int j = spawn.y - radius; j < spawn.y + radius; ++j) {
        //     for (int k = spawn.x - radius; k < spawn.y + radius; ++k) {
        //         middle_height += game->get_tilemap().get_tile(k, j).get_height();
        //     }
        // }
        //
        // middle_height /= (float)square;
        //
        // for (int j = spawn.y - radius; j < spawn.y + radius; ++j) {
        //     for (int k = spawn.x - radius; k < spawn.y + radius; ++k) {
        //         game->get_tilemap().get_tile(k, j).set_height(middle_height);
        //     }
        // }

        //stts::vector2<int> unit1_offset(-radius / 2, 0), unit2_offset(radius / 2, 0);

        // Base
        ent::unit& u_base = game->make_unit("base", i);
        game->get_tilemap().transpose(u_base, spawn + stts::vector2<int>(radius / 2, 0));

        // Units
        ent::unit& u_runner_1 = game->make_unit("solemn", i);
        game->get_tilemap().transpose(u_runner_1, spawn + stts::vector2<int>(-radius / 2, 0));

        /*if (unit1_offset != unit2_offset) { // TODO: remove this to test on SANE-SIZED maps
            ent::unit &u_runner_2 = game->make_unit("solemn", i);
            game->get_tilemap().transpose(u_runner_2, spawn + stts::vector2<int>(radius / 2, 0));
        }*/
    }

    return std::move(game);

}
