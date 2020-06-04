#ifndef LOGIC_LOGGER_TEST_HPP
#define LOGIC_LOGGER_TEST_HPP

#include "../../base/includes.hpp"

namespace unit_testing {
    void test_logger() {
        json j {"asap", 34};

        logger::enable_logger(false, l::loggers::user_logger);
        logger::enable_logger(false, l::loggers::broadcast_logger);

        logger::say(l::debug) << "Logger testing started..." << logger::out;
        logger::say() << "This is a not decorated message via stream output operator..." << logger::over << "...and this is a decorated one." << logger::out;
        logger::say() << "Stream operator accepts any types, including: (char) " << 'a' << ", (int) " << 128 << ", (float) " << 128.256 << ", und so weiter..." << logger::out;
        logger::say() << "It also accepts serialized type: (JSON) " << j << logger::out;
        logger::say() << "And here go some examples of logs send via special logger::say() function (with special modifiers):" << logger::out;
        logger::say() << "A warning string:" << logger::out;
        logger::say("That's the string!", l::warning);
        logger::say() << "An error number:" << logger::out;
        logger::say(404, l::error);
        logger::say() << "A special JSON:" << logger::out;
        logger::say(j, l::special);
        logger::say() << "Logger testing finished!" << logger::out;
        logger::say(l::debug) << logger::over;
    }
}

#endif //LOGIC_LOGGER_TEST_HPP
