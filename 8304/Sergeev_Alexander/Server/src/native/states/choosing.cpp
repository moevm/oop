#include "choosing.hpp"
#include "holding.hpp"
#include "playing.hpp"
#include "../online/session.hpp"
#include "../generators/abstract_generator.hpp"


states::choosing::choosing (online::session& context) : session(context) {
    session.game = nullptr;
}

const std::string& states::choosing::type () const {
    return j_choosing::type;
}

void states::choosing::game_update (json& output) {
    for (const auto& i : session.players_uid) {
        std::string uid = std::to_string(i);
        output[uid][j_typed::type] = online::j_session::type;
        output[uid][online::j_session::state] = session.state->type();
    }
}

void states::choosing::game_load (json& input, json& output) {
    session.game = json_tools::unpack_game(input[in_game_load::game]);
    if (session.game != nullptr) {
        output[out_signal::success] = LOCATED("The game was setup game type");
        session.transition_to(std::make_unique<states::holding>(session));
    }
    else {
        output[out_signal::error] = LOCATED("Broken saved game");
    }
}

void states::choosing::game_save (json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::choosing::game_join (int player_uid, json& output) {
    auto result = session.players_uid.emplace(player_uid); //TODO other type checks
    if (result.second) {
        output[out_signal::success] = LOCATED("Player was added into the room");
    }
    else {
        output[out_signal::success] = LOCATED("Player was already in the room...");
    }
}

void states::choosing::game_quit (int player_uid, json& output) {
    if (session.players_uid.erase(player_uid) != 0) {
        output[out_signal::success] = LOCATED("Player was removed from the room");
    }
    else {
        output[out_signal::error] = LOCATED("Player wasn't in the room");
    }
}

void states::choosing::game_play (json& output) {
    if (session.game != nullptr) {
        output[out_signal::success] = LOCATED("The game was started");
        session.transition_to(std::make_unique<playing>(session));
    }
    else {
        output[out_signal::error] = LOCATED("The game wasn't setup");
    }
}

void states::choosing::game_pause (json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::choosing::game_stop (json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::choosing::game_setup (json& input, json& output) {
    std::shared_ptr<generators::abstract_generator> generator = json_tools::unpack_generator(input[in_game_setup::generator]);
    session.game = generator->generate();
    if (session.game != nullptr) {
        output[out_signal::success] = LOCATED("The game was setup game type");
    }
    else {
        output[out_signal::error] = LOCATED("Unknown game type");
    }
}

void states::choosing::game_signal (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}








