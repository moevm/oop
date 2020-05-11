#pragma once

#include "../Units/units.hpp"
#include "command_memento.hpp"
#include "commands.hpp"
#include <sstream>

using namespace std;

class CommandCreateUnit : public Command {
public:
    CommandCreateUnit(Coordinates coors, UnitType unit_type)
        : coors(coors), unit_type(unit_type) {}

    void execute(Game* game) override {
        // rules do not allow unit creation
        if (!game->rule->can_create_units())
            return;

        Base* base = game->current_player->base;

        // not enough money
        if ((UNIT_COST > game->current_player->money) ||
            (game->current_player->units.size() >= PLAYER_MAX_UNITS)) {
            return;
        }

        // too far
        if (!game->field->can_reach(base->get_coors(), coors)) {
            return;
        }

        UnitInterface* unit = Unit::create_unit(unit_type);
        unit->set_owner(game->current_player);
        unit->set_owner_id(game->current_player_id);
        unit->set_moved(true);
        game->current_player->add_unit(unit);
        game->current_player->money -= UNIT_COST;

        *game->logger << "[PLAYER] Player " << *game->current_player
                      << " creates unit " << *unit << " at " << coors
                      << Logger::Endl();

        game->field->place_unit_at(coors, unit);
    }

    CommandMemento get_memento() override {
        stringstream str;
        str << "create " << coors << " " << unit_type;
        return CommandMemento(str.str());
    }

private:
    Coordinates coors;
    UnitType unit_type;
};

class CreateUnitCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return command.size() == 3 && command[0] == "create";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            Coordinates coors(command[1]);
            UnitType unit_type = static_cast<UnitType>(stoi(command[2]));
            return new CommandCreateUnit(coors, unit_type);
        } else if (next) {
            return next->handle(command);
        }
        return nullptr;
    };
};
