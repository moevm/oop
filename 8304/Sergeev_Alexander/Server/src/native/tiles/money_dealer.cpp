#include "money_dealer.hpp"
#include "base_tile.hpp"
#include "../entities/unit.hpp"

tile::money_dealer::money_dealer (float nheight, int nmoney) : tile::base_tile(nheight), money(nmoney) {}

tile::money_dealer::money_dealer (json& package) {
    money_dealer::deserialize(package);
}

void tile::money_dealer::serialize (json& package) const {
    base_tile::serialize(package);
    package[j_money_dealer::money] = money;
}

void tile::money_dealer::deserialize (json& package) {
    base_tile::deserialize(package);
    money = package[j_money_dealer::money].get<int>();
}

const std::string& tile::money_dealer::type () const {
    return j_money_dealer::type;
}

void tile::money_dealer::on_unit_enter (ent::unit& sender) {
    base_tile::on_unit_enter(sender);
}

void tile::money_dealer::on_unit_touch (ent::unit& sender, game::abstract_game& context) {
    base_tile::on_unit_touch(sender, context);
    json package;
    package[j_money_dealer::money] = money;
    sender.command(sender, context, com::j_miner::type, package);
}

void tile::money_dealer::on_unit_exit (ent::unit& sender) {
    base_tile::on_unit_exit(sender);
}





