#include "api.hpp"
#include "../filesys/file_gate.hpp"

online::api::api () {
    delta_time = 0;
    chat_buffer_updates = 0;
    chat_buffer = std::queue<stts::chat_message>();
    broadcast_buffer = std::queue<stts::broadcast_message>();
    sessions = std::map<int, std::shared_ptr<session>>();
}

void online::api::to_chat(stts::chat_message &msg) {
    chat_buffer.push(msg);
    if (chat_buffer.size() > (unsigned int)chat_capacity) chat_buffer.pop();
    chat_buffer_updates++;
}

void online::api::to_broadcast(stts::broadcast_message &msg) {
    broadcast_buffer.push(msg);
}



void online::api::start (json& config) {
    logger::say("Server started", l::special);

    delta_time = config[j_api::delta_time].get<float>();
    chat_capacity = config[j_api::chat_capacity].get<int>();
    file::file_gate::ROOT = config[j_api::root_folder].get<std::string>();
}

void online::api::update (json& output) {
    output[out_update::delta_time] = delta_time + 1;
    output[out_update::broadcast][j_typed::type] = out_broadcast::type;
    output[out_update::broadcast][out_broadcast::chat_buffer_updates] = chat_buffer_updates;
    for (const auto& item : sessions) {
        item.second->game_update(output[out_update::players_sessions][std::to_string(item.first)]);
    }
    logger::enable_all(false);
    logger::enable_logger(true, l::server_file_logger);
    logger::say() << output.dump() << logger::out;
    logger::enable_all(true);
}

void online::api::signal (json& input, json& output) {
    output[j_typed::type] = out_signal::type;
    if (input[j_typed::type] == nullptr || input[in_signal::sender] == nullptr) {
        output[out_signal::error] = LOCATED("Input isn't correct");
        return;
    }

    std::string type = input[j_typed::type];
    if (type == in_server_info::type) server_info(output);
    else if (type == in_read_chat::type) read_chat(output);
    else if (type == in_write_chat::type) write_chat(input, output);
    else if (type == in_create_session::type) create_session(input, output);
    else signal_session(input, output);
}

void online::api::server_info (json& output) {
    output[j_typed::type] = out_server_info::type;
    output[out_server_info::sessions] = json::object();
    for (const auto& item : sessions) {
        item.second->get_session_info(output[out_server_info::sessions][std::to_string(item.first)]);
    }
}

void online::api::read_chat (json& output) {
    output[j_typed::type] = out_read_chat::type;
    json_tools::pack_queue(chat_buffer, output[out_read_chat::chat_buffer]);
}

void online::api::write_chat (json& input, json& output) {
    output[j_typed::type] = out_write_chat::type;
    if (input[in_write_chat::message] == nullptr) {
        output[out_signal::error] = LOCATED("Input isn't correct");
        return;
    }
    if (input[in_write_chat::message] == "") {
        output[out_signal::error] = LOCATED("Message is empty");
        return;
    }
    int player_uid = input[in_signal::sender].get<int>();
    chat_buffer.push(stts::chat_message(player_uid, input[in_write_chat::message]));
    if (chat_buffer.size() > (size_t)chat_capacity) chat_buffer.pop();
    chat_buffer_updates++;
    //TODO important game events into write_chat (or log) (for example, logger::setup_lobby(this) then use logger::log_chat();
}

void online::api::create_session (json& input, json& output) {
    output[j_typed::type] = out_create_session::type;
    if (input[in_create_session::session_name] == nullptr) {
        output[out_signal::error] = LOCATED("Input isn't correct");
        return;
    }
    int session_id = 1;
    while (sessions[session_id] != nullptr) session_id++;
    sessions[session_id] = std::make_shared<session>(input[in_create_session::session_name]);
    output[out_create_session::session_id] = session_id;
}

void online::api::signal_session (json& input, json& output) {
    output[j_typed::type] = out_signal_session::type;
    if (input[in_signal_session::session_id] == nullptr) {
        output[out_signal::error] = LOCATED("Input isn't correct");
        return;
    }

    int session_id = input[in_signal_session::session_id].get<int>();
    auto iter = sessions.find(session_id);
    if (iter == sessions.end()) {
        output[out_signal::error] = LOCATED("Session wasn't found");
        return;
    }
    std::shared_ptr<session> session = iter->second;

    std::string type = input[j_typed::type];
    if (type == in_session_info::type) session->get_session_info(output);
    else if (type == in_game_info::type) session->get_game_info(output);
    else if (type == in_game_load::type) session->game_load(input, output);
    else if (type == in_game_save::type) session->game_save(output);
    else if (type == in_game_join::type) session->game_join(input[in_signal::sender].get<int>(), output);
    else if (type == in_game_quit::type) session->game_quit(input[in_signal::sender].get<int>(), output);
    else if (type == in_game_play::type) session->game_play(output);
    else if (type == in_game_pause::type) session->game_pause(output);
    else if (type == in_game_stop::type) session->game_stop(output);
    else if (type == in_game_setup::type) session->game_setup(input, output);
    else if (type == in_game_signal::type) session->game_signal(input, output);
    else output[out_signal::error] = LOCATED("Type isn't correct");

    if (session->get_player_count() == 0) {
        sessions.erase(session_id);
        output[out_signal::success] = "Session was deleted";
    }
}
