#ifndef LOGIC_CHAT_MESSAGE_HPP
#define LOGIC_CHAT_MESSAGE_HPP


#include "../base/includes.hpp"

namespace stts {
    // JSON
    namespace j_chat_message {
        const std::string player_uid = TOSTRING(player_uid); // : int
        const std::string message = TOSTRING(message); // : string
    }

    class chat_message : public iserializable {
    public:
        int player_uid;
        std::string message;

    public:
        explicit chat_message (int nplayer_uid, const std::string& nmessage);
        explicit chat_message (json& package);
        chat_message (const chat_message& other);
        chat_message& operator= (const chat_message& other);
        void serialize (json& package) const final;
        void deserialize (json& package) final;
    };
}

#endif //LOGIC_CHAT_MESSAGE_HPP
