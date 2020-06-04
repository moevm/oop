#ifndef LOGIC_CONSTANTS_RESPONSES_HPP
#define LOGIC_CONSTANTS_RESPONSES_HPP

#include "third_party_includes.hpp"

// JSON

namespace out_update { // Server side, there is session on client side
    const std::string delta_time = TOSTRING(delta_time); // : float
    const std::string broadcast = TOSTRING(broadcast); // : out_broadcast
    const std::string players_sessions = TOSTRING(players_sessions); // : map<int = session_id, map<int = player_id, session>>
}

namespace out_broadcast { // : j_typed
    const std::string type = TOSTRING(out_broadcast);
    const std::string chat_buffer_updates = TOSTRING(chat_buffer_updates); // : int (to read_chat on change)
}

namespace out_signal { // : j_typed
    const std::string type = TOSTRING(out_signal);
    const std::string error = TOSTRING(error); // : string?
    const std::string success = TOSTRING(success); // : string?
}

namespace out_server_info { // : out_signal
    const std::string type = TOSTRING(out_server_info);
    const std::string sessions = TOSTRING(sessions); // : map<int, out_session_info>
}

namespace out_read_chat { // : out_signal
    const std::string type = TOSTRING(out_read_chat);
    const std::string chat_buffer = TOSTRING(chat_buffer); // : queue<chat_message>?
}

namespace out_write_chat { // : out_signal
    const std::string type = TOSTRING(out_write_chat);
}

namespace out_create_session { // : out_signal
    const std::string type = TOSTRING(out_create_session);
    const std::string session_id = TOSTRING(session_id); // int
}

namespace out_signal_session { // : out_signal
    const std::string type = TOSTRING(out_signal_session);
}

namespace out_session_info { // : out_signal_session
    const std::string type = TOSTRING(out_session_info);
    const std::string session = TOSTRING(session); // : session
}

namespace out_game_info { // : out_signal_session
    const std::string type = TOSTRING(out_game_info);
    const std::string game_data = TOSTRING(game_data); // : abstract_game?
}

namespace out_game_load { // : out_signal_session
    const std::string type = TOSTRING(out_game_load);
}

namespace out_game_save { // : out_signal_session
    const std::string type = TOSTRING(out_game_save);
    const std::string game = TOSTRING(game); // : base_game?
}

namespace out_game_join { // : out_signal_session
    const std::string type = TOSTRING(out_game_join);
    const std::string session_id = TOSTRING(session_id); // int
}

namespace out_game_quit { // : out_signal_session
    const std::string type = TOSTRING(out_game_quit);
}

namespace out_game_play { // : out_signal_session
    const std::string type = TOSTRING(out_game_play);
}

namespace out_game_pause { // : out_signal_session
    const std::string type = TOSTRING(out_game_pause);
}

namespace out_game_stop { // : out_signal_session
    const std::string type = TOSTRING(out_game_stop);
}

namespace out_game_setup { // : out_signal_session
    const std::string type = TOSTRING(out_game_setup);
}

namespace out_game_signal { // : out_signal_session
    const std::string type = TOSTRING(out_game_signal);
}

#endif //LOGIC_CONSTANTS_RESPONSES_HPP
