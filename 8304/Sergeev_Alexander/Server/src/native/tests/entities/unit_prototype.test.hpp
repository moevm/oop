#ifndef LOGIC_UNIT_PROTOTYPE_TEST_HPP
#define LOGIC_UNIT_PROTOTYPE_TEST_HPP

#include "../../base/includes.hpp"
#include "../../entities/unit_prototype.hpp"

namespace unit_testing {
    void test_unit_prototype() {
        std::cout << "* test_unit_prototype [started]" << std::endl;

        const std::string name = "proto_1";

        ent::unit_prototype proto_1 = ent::unit_prototype(name);
        assert(proto_1.get_name() == name);


        proto_1.add_component(com::j_move::type);
        //proto_1.


        std::cout << "* test_unit_prototype [success]" << std::endl;
    }
}

#endif //LOGIC_UNIT_PROTOTYPE_TEST_HPP
