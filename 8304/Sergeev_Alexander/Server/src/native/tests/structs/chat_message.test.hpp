#ifndef LOGIC_CHAT_MESSAGE_TEST_HPP
#define LOGIC_CHAT_MESSAGE_TEST_HPP

#include "../../base/includes.hpp"
#include "../../structs/chat_message.hpp"

namespace unit_testing {
    void test_chat_message() {
        logger::say(l::debug) << "Chat message testing started..." << logger::out;
        logger::say() << "Creating chat message from player -1 with text \"Sample text\"" << logger::out;
        stts::chat_message msg(-1, "Sample text");
        logger::say()  << "Serializing it" << logger::out;
        json j;
        msg.serialize(j);
        logger::say()  << "Serialized: " << j << logger::out;
        logger::say() << "Creating from JSON (via copying operator)" << logger::out;
        stts::chat_message nmsg = stts::chat_message(j);
        logger::say(l::debug) << "Success!" << logger::out;
        logger::say(l::debug) << "Chat message testing finished!" << logger::out;
        logger::say() << logger::over;
    }
}

#endif //LOGIC_CHAT_MESSAGE_TEST_HPP
