#ifndef LOGIC_VECTOR2_TEST_HPP
#define LOGIC_VECTOR2_TEST_HPP

#include "../../base/includes.hpp"
#include "../../structs/vector2.hpp"

namespace unit_testing {
    void test_vector2() {
        logger::say(l::debug) << "Vector2 testing started..." << logger::out;
        logger::say() << "Creating a int vector2 with values 0, 0" << logger::out;
        stts::vector2<int> v2int = stts::vector2<int>();
        logger::say() << "Checking if the vector is set: " << v2int.is_set() << logger::out;
        json j;
        v2int.serialize(j);
        logger::say()  << "Serialized: " << j << logger::out;
        logger::say() << "Assigning it to -1, -1 (default error vector)" << logger::out;
        v2int.x = -1;
        v2int.y = -1;
        logger::say() << "Checking if the vector is set: " << v2int.is_set() << logger::out;
        j = {};
        v2int.serialize(j);
        logger::say()  << "Serialized: " << j << logger::out;
        logger::say() << "Creating from JSON (via copying operator)" << logger::out;
        stts::vector2<int> v2int2 = stts::vector2<int>(j);
        logger::say(l::debug) << "Success!" << logger::out;
        logger::say() << "Creating a double vector2 with values 6.123, 163.9045" << logger::out;
        stts::vector2<double> v2double = stts::vector2<double>(6.123, 163.9045);
        j = {};
        v2double.serialize(j);
        logger::say()  << "Serialized: " << j << logger::out;
        logger::say() << "Creating via copying constructor" << logger::out;
        stts::vector2<double> v2double2 = stts::vector2<double>(v2double);
        logger::say(l::debug) << "Success!" << logger::out;
        logger::say() << "Checking if newly created vector is equal to prototype: " << (v2double2 == v2double) << logger::out;
        v2double2 = -v2double2;
        j = {};
        v2double2.serialize(j);
        logger::say()  << "-(Second vector) = " << j << logger::out;
        logger::say() << "Checking if newly created vector is not equal to prototype: " << (v2double2 != v2double) << logger::out;
        v2double = v2double - v2double2;
        j = {};
        v2double.serialize(j);
        logger::say()  << "First vector = First vector - Second vector = " << j << logger::out;
        v2double2 = v2double2 + v2double;
        j = {};
        v2double2.serialize(j);
        logger::say()  << "Second vector = Second vector + First vector = " << j << logger::out;
        logger::say()  << "First vector * Second vector = " << v2double * v2double2 << logger::out;
        logger::say() << "Magnitude of first vector = " << v2double.magnitude() << logger::out;
        logger::say() << "Square magnitude of first vector = " << v2double.sqr_magnitude() << logger::out;
        logger::say(l::debug) << "Vector2 testing finished!" << logger::out;
        logger::say() << logger::over;
    }
}

#endif //LOGIC_VECTOR2_TEST_HPP
