#include "logger_user.hpp"
#include "../online/api.hpp"

#define SERVER_ID -1



void l::logger_user::let (std::string& verbal, streams stream, bool decorated) {
    std::stringstream ss;
    ss << (char) stream << "! " << verbal;
    std::string timed_verbal = decorated ? ss.str() : verbal;
    stts::chat_message msg(int(SERVER_ID), timed_verbal);
    online::api::get().to_chat(msg);
}
