#include "session.hpp"
#include "../states/choosing.hpp"

online::session::session (const std::string& nsession_name) {
    session_name = nsession_name;
    players_uid = std::set<int>();
    state = std::make_unique<states::choosing>(*this);
    game = nullptr;
}

const std::string& online::session::type () const {
    return j_session::type;
}

std::string online::session::get_session_name () {
    return session_name;
}

int online::session::get_player_count () {
    return players_uid.size();
}

void online::session::get_session_info (json& output) {
    output[j_typed::type] = out_session_info::type;
    output[out_session_info::session][j_typed::type] = j_session::type;
    output[out_session_info::session][j_session::session_name] = get_session_name();
    output[out_session_info::session][j_session::state] = state->type();
    output[out_session_info::session][j_session::players_uid] = players_uid;
}

void online::session::get_game_info (json& output) {
    output[j_typed::type] = out_game_info::type;
    if (game) game->serialize_public(output[out_game_info::game_data]);
}

void online::session::game_update (json& output) {
    std::cout << "updating" << session_name;
    state->game_update(output);
}

void online::session::game_load (json& input, json& output) {
    output[j_typed::type] = out_game_load::type;
    state->game_load(input, output);
}

void online::session::game_save (json& output) {
    output[j_typed::type] = out_game_save::type;
    state->game_save(output);
}

void online::session::game_join (int player_uid, json& output) {
    output[j_typed::type] = out_game_join::type;
    state->game_join(player_uid, output);
}

void online::session::game_quit (int player_uid, json& output) {
    output[j_typed::type] = out_game_quit::type;
    state->game_quit(player_uid, output);
}

void online::session::game_play (json& output) {
    output[j_typed::type] = out_game_play::type;
    state->game_play(output);
}

void online::session::game_pause (json& output) {
    output[j_typed::type] = out_game_pause::type;
    state->game_pause(output);
}

void online::session::game_stop (json& output) {
    output[j_typed::type] = out_game_stop::type;
    state->game_stop(output);
}

void online::session::game_setup (json& input, json& output) {
    output[j_typed::type] = out_game_setup::type;
    state->game_setup(input, output);
}

void online::session::game_signal (json& input, json& output) {
    output[j_typed::type] = out_game_signal::type;
    state->game_signal(input, output);
}

void online::session::transition_to (std::unique_ptr<ihandler> nstate) {
    logger::say() << "Game state changed to " << nstate->type() << logger::out;
    state = std::move(nstate);
}











