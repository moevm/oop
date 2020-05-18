#pragma once

#include "command_memento.hpp"
#include "commands.hpp"

class CommandEndGame : public Command {
public:
    CommandEndGame() {}
    void execute(Game* game) override { game->set_running(false); }
    CommandMemento get_memento() override { return CommandMemento("end"); };
    bool save_to_history() { return false; }
};

class EndGameCommandHandler : public CommandHandler {
public:
    bool can_handle(vector<string> command) {
        return command.size() == 1 && command[0] == "end";
    }

    Command* handle(vector<string> command) {
        if (can_handle(command)) {
            return new CommandEndGame;
        } else if (next) {
            return next->handle(command);
        }
        return nullptr;
    };
};
