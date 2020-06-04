#include "playing.hpp"
#include "choosing.hpp"
#include "holding.hpp"
#include "../online/session.hpp"


states::playing::playing (online::session& context) : session(context) { }

const std::string& states::playing::type () const {
    return j_playing::type;
}

void states::playing::game_update (json& output) {
    session.game->update(output);
    bool is_finished = session.game->is_finished();
    for (const auto& i : session.players_uid) {
        std::string uid = std::to_string(i);
        output[uid][j_typed::type] = online::j_session::type;
        output[uid][online::j_session::state] = session.state->type();
        if (is_finished) session.game->serialize(output[uid][online::j_session::game]);
        else session.game->serialize_concrete_player(i, output[uid][online::j_session::game]);
    }
    if (is_finished) session.transition_to(std::make_unique<states::choosing>(session));
}

void states::playing::game_load (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::playing::game_save (json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::playing::game_join (int player_uid, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::playing::game_quit (int player_uid, json& output) {
    output[out_signal::error] = LOCATED("Connection lost. You can rejoin");
}

void states::playing::game_play (json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::playing::game_pause (json& output) {
    session.transition_to(std::make_unique<states::holding>(session));
    output[out_signal::success] = LOCATED("The game was paused");
}

void states::playing::game_stop (json& output) {
    session.transition_to(std::make_unique<states::choosing>(session));
    output[out_signal::success] = LOCATED("The game was stopped");
}

void states::playing::game_setup (json& input, json& output) {
    output[out_signal::error] = LOCATED("Wrong transition");
}

void states::playing::game_signal (json& input, json& output) {
    // TODO maybe try catch with success/error response to client
    session.game->signal(input, output);
}


