#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Boardfield.h"
#include "Base.h"


TEST_CASE("Test of adding units", "" ) {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);

    result = a.add_unit(b, 0, 5, 1);
    REQUIRE(!result);

    result = a.add_unit(b, 0, 0, 2);
    REQUIRE(!result);

    REQUIRE(b.current_size == 1);
}


TEST_CASE("Test of moving units", "" ) {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);

    result = a.move_unit(0, 0, 4, 3);
    REQUIRE(result);

    result = a.move_unit(4, 3, 0, 0);
    REQUIRE(result);

    result = a.add_unit(b, 1, 4, 4);
    REQUIRE(result);

    result = a.move_unit(1, 4, 0, 0);
    REQUIRE(!result);

    REQUIRE(b.current_size == 2);

    result = a.add_unit(b, 4, 4, 3);
    REQUIRE(!result);

    a.get_boardfield();
}

TEST_CASE("Test of deleting units", "" ) {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);
    REQUIRE(b.current_size == 1);

    result = a.delete_unit(0, 0);
    REQUIRE(result);
    REQUIRE(b.current_size == 0);

    result = a.delete_unit(3, 4);
    REQUIRE(!result);
}
