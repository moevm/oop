#include "chat_message.hpp"


stts::chat_message::chat_message (int nplayer_uid, const std::string& nmessage) {
    player_uid = nplayer_uid;
    message = nmessage;
}

stts::chat_message::chat_message (json& package) {
    deserialize(package);
}

stts::chat_message::chat_message (const chat_message& other) : player_uid(other.player_uid), message(other.message) { }

stts::chat_message& stts::chat_message::operator= (const chat_message& other) {
    if (this != &other) {
        player_uid = other.player_uid;
        message = other.message;
    }
    return *this;
}

void stts::chat_message::serialize (json& package) const {
    package[j_chat_message::player_uid] = player_uid;
    package[j_chat_message::message] = message;
}

void stts::chat_message::deserialize (json& package) {
    player_uid = package[j_chat_message::player_uid].get<int>();
    message = package[j_chat_message::message].get<std::string>();
}
