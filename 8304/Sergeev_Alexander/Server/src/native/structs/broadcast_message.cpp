#include "broadcast_message.hpp"


stts::broadcast_message::broadcast_message (int nstream, const std::string& nmessage) {
    stream = nstream;
    message = nmessage;
}

stts::broadcast_message::broadcast_message (json& package) {
    deserialize(package);
}

stts::broadcast_message::broadcast_message (const broadcast_message& other) : stream(other.stream), message(other.message) { }

stts::broadcast_message& stts::broadcast_message::operator= (const broadcast_message& other) {
    if (this != &other) {
        stream = other.stream;
        message = other.message;
    }
    return *this;
}

void stts::broadcast_message::serialize (json& package) const {
    package[j_broadcast_message::stream] = stream;
    package[j_broadcast_message::message] = message;
}

void stts::broadcast_message::deserialize (json& package) {
    stream = package[j_broadcast_message::stream].get<int>();
    message = package[j_broadcast_message::message].get<std::string>();
}
