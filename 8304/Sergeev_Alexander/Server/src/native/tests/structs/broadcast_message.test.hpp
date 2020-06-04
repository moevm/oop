#ifndef LOGIC_BROADCAST_MESSAGE_TEST_HPP
#define LOGIC_BROADCAST_MESSAGE_TEST_HPP

#include "../../base/includes.hpp"
#include "../../structs/broadcast_message.hpp"

namespace unit_testing {
    void test_broadcast_message() {
        logger::say(l::debug) << "Broadcast message testing started..." << logger::out;
        logger::say() << "Creating broadcast message in stream l::error with text \"Sample text\"" << logger::out;
        stts::broadcast_message msg(l::error, "Sample text");
        logger::say()  << "Serializing it" << logger::out;
        json j;
        msg.serialize(j);
        logger::say()  << "Serialized: " << j << logger::out;
        logger::say() << "Creating from JSON (via copying operator)" << logger::out;
        stts::broadcast_message nmsg = stts::broadcast_message(j);
        logger::say(l::debug) << "Success!" << logger::out;
        logger::say(l::debug) << "Broadcast message testing finished!" << logger::out;
        logger::say() << logger::over;
    }
}

#endif //LOGIC_BROADCAST_MESSAGE_TEST_HPP
