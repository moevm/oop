#ifndef LOGIC_PARAMETER_MAP_TEST_HPP
#define LOGIC_PARAMETER_MAP_TEST_HPP

#include "../../base/includes.hpp"
#include "../../structs/parameter_map.hpp"

namespace unit_testing {
    void test_parameter_map() {
        logger::say(l::debug) << "Parameter map testing started..." << logger::out;
        logger::say() << "Creating a parameter map with sets of two parameters of each kind" << logger::out;
        stts::parameter_map map;
        map.set("bool 1", true);
        map.set("bool 2", false);
        map.set("int 1", 42);
        map.set("int 2", 228);
        map.set("float 1", 3.1415);
        map.set("float 2", 2.718);
        map.set("string 1", "sample text");
        map.set("string 2", "SaMpLe TeXt");
        map.set("vector2<int> 1", stts::vector2<int>(789345, 873587));
        map.set("vector2<int> 2", stts::vector2<int>(3, 8));
        map.set("vector2<float> 1", stts::vector2<float>(2.785789375, 3.7896578345));
        map.set("vector2<float> 2", stts::vector2<float>(123.8754785, 90.87453874));
        map.set("vector2<vector2<int>> 1", stts::vector2<stts::vector2<int>>(stts::vector2<int>(345, 456), stts::vector2<int>(567, 678)));
        map.set("vector2<vector2<int>> 2", stts::vector2<stts::vector2<int>>(stts::vector2<int>(-1, 0), stts::vector2<int>(0, 1)));
        logger::say()  << "Serializing it" << logger::out;
        json j;
        map.serialize(j);
        logger::say()  << "Serialized: " << j << logger::out;
        logger::say() << "Creating from JSON" << logger::out;
        stts::chat_message nmap(j);
        logger::say(l::debug) << "Success!" << logger::out;
        logger::say(l::debug) << "Parameter map testing finished!" << logger::out;
        logger::say() << logger::over;
    }
}

#endif //LOGIC_PARAMETER_MAP_TEST_HPP
