#ifndef LOGIC_CONSTANTS_REQUESTS_HPP
#define LOGIC_CONSTANTS_REQUESTS_HPP

#include "third_party_includes.hpp"

// JSON

namespace in_signal { // : j_typed
    const std::string type = TOSTRING(in_signal);
    const std::string sender = TOSTRING(sender); // : int
}

namespace in_server_info { // : in_signal
    const std::string type = TOSTRING(in_server_info);
}

namespace in_read_chat { // : in_signal
    const std::string type = TOSTRING(in_read_chat);
}

namespace in_write_chat { // : in_signal
    const std::string type = TOSTRING(in_write_chat);
    const std::string message = TOSTRING(message); // : string
}

namespace in_create_session { // : in_signal
    const std::string type = TOSTRING(in_create_session);
    const std::string session_name = TOSTRING(session_name); // : string
}

namespace in_signal_session { // : in_signal
    const std::string type = TOSTRING(in_signal_session);
    const std::string session_id = TOSTRING(session_id); // : int
}

namespace in_session_info { // : in_signal_session
    const std::string type = TOSTRING(in_session_info);
}

namespace in_game_info { // : in_signal_session
    const std::string type = TOSTRING(in_game_info);
}

namespace in_game_load { // : in_signal_session
    const std::string type = TOSTRING(in_game_load);
    const std::string game = TOSTRING(game); // : abstract_game?
}

namespace in_game_save { // : in_signal_session
    const std::string type = TOSTRING(in_game_save);
}

namespace in_game_join { // : in_signal_session
    const std::string type = TOSTRING(in_game_join);
}

namespace in_game_quit { // : in_signal_session
    const std::string type = TOSTRING(in_game_quit);
}

namespace in_game_play { // : in_signal_session
    const std::string type = TOSTRING(in_game_play);
}

namespace in_game_pause { // : in_signal_session
    const std::string type = TOSTRING(in_game_pause);
}

namespace in_game_stop { // : in_signal_session
    const std::string type = TOSTRING(in_game_stop);
}

namespace in_game_setup { // : in_signal_session
    const std::string type = TOSTRING(in_game_setup);
    const std::string generator = TOSTRING(generator); // : abstract_generator
}

namespace in_game_signal { // : in_signal_session
    const std::string type = TOSTRING(in_game_signal);
    const std::string units = TOSTRING(units); // : list<int>
    const std::string component = TOSTRING(component); // : string
    const std::string data = TOSTRING(data); // : j_{command_name}
}


#endif //LOGIC_CONSTANTS_REQUESTS_HPP
