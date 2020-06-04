#ifndef LOGIC_BROADCAST_MESSAGE_HPP
#define LOGIC_BROADCAST_MESSAGE_HPP


#include "../base/includes.hpp"

namespace stts {
    // JSON
    namespace j_broadcast_message {
        const std::string stream = TOSTRING(stream); // : char
        const std::string message = TOSTRING(message); // : string
    }

    class broadcast_message : public iserializable {
    public:
        int stream;
        std::string message;

    public:
        explicit broadcast_message (int nstream, const std::string& nmessage);
        explicit broadcast_message (json& package);
        broadcast_message (const broadcast_message& other);
        broadcast_message& operator= (const broadcast_message& other);
        void serialize (json& package) const final;
        void deserialize (json& package) final;
    };
}


#endif //LOGIC_BROADCAST_MESSAGE_HPP
