#include "holding.hpp"
#include "choosing.hpp"
#include "playing.hpp"
#include "../online/session.hpp"


states::holding::holding (online::session& context) : session(context) { }

const std::string& states::holding::type () const {
    return j_holding::type;
}

void states::holding::game_update (json& output) {
    bool is_finished = session.game->is_finished();
    for (const auto& i : session.players_uid) {
        std::string uid = std::to_string(i);
        output[uid][j_typed::type] = online::j_session::type;
        output[uid][online::j_session::state] = session.state->type();
        if (is_finished) session.game->serialize(output[uid][online::j_session::game]);
        else session.game->serialize_concrete_player(i, output[uid][online::j_session::game]);
    }
}

void states::holding::game_load (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_save (json& output) {
    session.game->serialize(output[out_game_save::game]);
    output[out_signal::success] = LOCATED("Game saved");
}

void states::holding::game_join (int player_uid, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_quit (int player_uid, json& output) {
    output[out_signal::error] = LOCATED("Connection lost. You can rejoin");
}

void states::holding::game_play (json& output) {
    session.transition_to(std::make_unique<playing>(session));
    output[out_signal::success] = LOCATED("The game was continued");
}

void states::holding::game_pause (json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_stop (json& output) {
    session.transition_to(std::make_unique<states::choosing>(session));
    output[out_signal::success] = LOCATED("The game was stopped");
}

void states::holding::game_setup (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::holding::game_signal (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}



