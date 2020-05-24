#pragma once

#include "../Logging/formatter.hpp"
#include "../Logging/logger_proxy.hpp"
#include "Field/coordinates.hpp"
#include "Field/field_proxy.hpp"
#include "Player/player.hpp"
#include "Rules/game_rule.hpp"
#include "Tiles/base.hpp"
#include "Units/concrete_unit_factory.hpp"
#include "Units/units.hpp"

class Game {
public:
    LoggerProxy* logger;

    GameRule* rule;

    FieldProxy* field;
    vector<Player*> players;

    Player* current_player;
    unsigned current_player_id;

    Game();
    ~Game();

    void end_game();
    void new_game(unsigned width, unsigned height, unsigned players_n);
    void next_player();

    void move_unit(Coordinates from_coors, Coordinates to_coors);
    void unit_action(Coordinates from_coors, Coordinates to_coors);
    void create_unit(Coordinates coors, UnitFactory* factory);

    bool is_owned_by(unsigned id, UnitInterface* unit);
    void spawn_powerup();

    vector<Coordinates> get_reachable(Coordinates coors);
    bool is_running() { return running; };
    bool unit_can_move(UnitInterface* unit);

    void set_logger(Logger* logger_) { logger->set_logger(logger_); };
    void set_log_formatter(LogFormatter* formatter) {
        logger->set_formatter(formatter);
    };

private:
    bool running;
};
