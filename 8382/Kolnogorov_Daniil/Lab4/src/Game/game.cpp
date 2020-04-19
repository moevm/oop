#include "game.hpp"
#include "Neutral/neutral_context.hpp"
#include "Neutral/powerup.hpp"

using namespace std;

Game::Game() {
    logger = new LoggerProxy();
    field = nullptr;
    rule = nullptr;
    current_player = nullptr;
    running = true;
}

Game::~Game() {
    delete logger;
    delete field;
    delete rule;
    for (auto player : players)
        delete player;
}

void Game::new_game(unsigned width, unsigned height, unsigned players_n) {
    delete field;
    delete rule;
    for (auto player : this->players) {
        delete player;
    }
    this->players.clear();
    current_player = nullptr;
    current_player_id = -1;

    field = new FieldProxy(width, height);

    rule = new GameRuleRegular();
    // rule = new GameRuleDeathmatch();
    rule->initialize_game(this, players_n);
    *logger << "[GAME] Starting new game with field size (" << width << ", "
            << height << ") and " << players_n << " players" << Logger::Endl();

    // spawn powerups
    unsigned initial_powerups = width * height / 80;
    for (unsigned count = 0; count < initial_powerups; count++) {
        spawn_powerup();
    }

    running = true;
}

void Game::end_game() {
    running = false;
}

void Game::next_player() {
    rule->next_player(this);
    *logger << "[GAME] Passing turn to player " << *current_player
            << Logger::Endl();
}

void Game::move_unit(Coordinates from_coors, Coordinates to_coors) {
    UnitInterface* unit = field->unit_at(from_coors);

    if (!is_owned_by(current_player_id, unit) ||
        !rule->unit_can_move(this, unit)) {
        return;
    }

    if (!field->can_reach(from_coors, to_coors)) {
        return;
    }

    *logger << "[GAME] Moving unit from " << from_coors << " to " << to_coors
            << Logger::Endl();

    field->move_unit(from_coors, to_coors);

    TileInterface* tile_new = field->tile_at(to_coors);
    if (tile_new->get_neutral()) {
        *logger << "[GAME] Applying neutral object to unit at " << to_coors
                << Logger::Endl();
        NeutralInterface* neutral = tile_new->get_neutral();
        NeutralContext neutral_cont;
        neutral_cont.set_neutral(neutral);
        neutral_cont.apply_to_unit(unit);
        neutral_cont.apply_to_player(current_player);
        tile_new->set_neutral(nullptr);
    }
}

void Game::unit_action(Coordinates from_coors, Coordinates to_coors) {
    TileInterface* tile_from = field->tile_at(from_coors);
    UnitInterface* unit = tile_from->get_unit();

    if (!unit)
        return;

    if (field->unit_can_move_to(to_coors)) {
        move_unit(from_coors, to_coors);
    } else if (!unit->get_attacked() &&
               Coordinates::distance_manh(from_coors, to_coors) <=
                   unit->get_range()) {
        *logger << "[UNIT] Unit at " << from_coors << " damages tile at "
                << to_coors << " for " << unit->get_strength() << " HP"
                << Logger::Endl();
        field->damage_tile(to_coors, unit->get_strength());
        unit->set_attacked(true);
    }
}

void Game::create_unit(Coordinates coors, UnitFactory* factory) {
    // rules do not allow unit creation
    if (!rule->can_create_units())
        return;

    Base* base = current_player->base;

    // not enough money
    if ((UNIT_COST > current_player->money) ||
        (current_player->units.size() >= PLAYER_MAX_UNITS)) {
        return;
    }

    // too far
    if (!field->can_reach(base->get_coors(), coors)) {
        return;
    }

    UnitInterface* unit = factory->create();
    unit->set_owner(current_player);
    unit->set_owner_id(current_player_id);
    unit->set_moved(true);
    current_player->add_unit(unit);
    current_player->money -= UNIT_COST;

    *logger << "[PLAYER] Player " << *current_player << " creates unit "
            << *unit << " at " << coors << Logger::Endl();

    field->place_unit_at(coors, unit);
}

void Game::spawn_powerup() {
    Coordinates coors = field->random_empty();
    NeutralInterface* powerup = (NeutralInterface*)Powerup::random_powerup();
    field->place_neutral_at(coors, powerup);
}

vector<Coordinates> Game::get_reachable(Coordinates coors) {
    return field->get_reachable(coors);
}

bool Game::unit_can_move(UnitInterface* unit) {
    return rule->unit_can_move(this, unit);
}

bool Game::is_owned_by(unsigned id, UnitInterface* unit) {
    return id == unit->get_owner_id();
}
