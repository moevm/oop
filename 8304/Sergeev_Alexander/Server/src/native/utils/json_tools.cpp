#include "json_tools.hpp"
#include "../game/abstract_game.hpp"
#include "../game/realtime.hpp"
#include "../game/stepped.hpp"
#include "../tilemap/abstract_tilemap.hpp"
#include "../tilemap/hexagonal.hpp"
#include "../tilemap/square.hpp"
#include "../generators/abstract_generator.hpp"
#include "../generators/perlin.hpp"
#include "../generators/simple.hpp"
#include "../rules/abstract_rule.hpp"
#include "../rules/deadmatch.hpp"
#include "../rules/skirmish.hpp"
#include "../rules/teams_skirmish.hpp"


std::unique_ptr<game::abstract_game> nlohmann::json_tools::unpack_game (json& package) {
    if (!package.contains(j_typed::type)) throw deserialization_exception("Package does not contain game");

    std::string type = package[j_typed::type];
    if (type == game::j_stepped::type) return std::make_unique<game::stepped>(package);
    else if (type == game::j_realtime::type) return std::make_unique<game::realtime>(package);
    else throw type_exception("Unknown game type");
}

std::unique_ptr<generators::abstract_generator> json_tools::unpack_generator (json& package) {
    if (!package.contains(j_typed::type)) throw deserialization_exception("Package does not contain generator");

    std::string type = package[j_typed::type];
    if (type == generators::j_simple::type) return std::make_unique<generators::simple>(package);
    else if (type == generators::j_perlin::type) return std::make_unique<generators::perlin>(package);
    else throw type_exception("Unknown generator type");
}

std::unique_ptr<rules::abstract_rule> json_tools::unpack_rule (json& package) {
    if (!package.contains(j_typed::type)) throw deserialization_exception("Package does not contain rules");

    std::string type = package[j_typed::type];
    if (type == rules::j_skirmish::type) return std::make_unique<rules::skirmish>(package);
    //else if (type == game::deadmathchetc::type) return std::make_unique<game::realtime>(package);
    else throw type_exception("Unknown rule type");
}

std::unique_ptr<tilemap::abstract_tilemap> nlohmann::json_tools::unpack_tilemap (json& package) {
    if (!package.contains(j_typed::type)) throw deserialization_exception("Package does not contain tilemap");

    std::string type = package[j_typed::type];
    if (type == tilemap::j_hexagonal::type) return std::make_unique<tilemap::hexagonal>(package);
    else if (type == tilemap::j_square::type) return std::make_unique<tilemap::square>(package);
    else throw type_exception("Unknown tilemap type");
}

tile::base_tile* nlohmann::json_tools::unpack_tile (json& package) {
    if (!package.contains(j_typed::type)) throw deserialization_exception("Package does not contain tile");

    std::string type = package[j_typed::type];
    if (type == tile::j_base_tile::type) return new tile::base_tile(package);
    else if (type == tile::j_damage_dealer::type) return new tile::damage_dealer(package);
    else if (type == tile::j_money_dealer::type) return new tile::money_dealer(package);
    else throw type_exception("Unknown tile type");
}

void nlohmann::json_tools::print_tilemap (tilemap::abstract_tilemap& tilemap) {
    std::cout << "[abstract_tilemap] " << tilemap.scale.x << "x" << tilemap.scale.y << std::endl;
    for (int ny = 0; ny < tilemap.scale.y; ++ny) {
        for (int nx = 0; nx < tilemap.scale.x; ++nx) {
            tile::base_tile& t = tilemap.get_tile(nx, ny);
            if (t.is_occupied()) {
                 std::cout << t.get_occupier_id() << "  ";
            }
            else if (t.type() == tile::j_damage_dealer::type) {
                std::cout << "-  ";
            }
            else if (t.type() == tile::j_money_dealer::type) {
                std::cout << "+  ";
            }
            else {
                std::cout << ",  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

