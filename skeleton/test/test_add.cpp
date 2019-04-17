#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "lib/add.hpp"

TEST_CASE("Make integers great again")
{
    auto n1 = 1;
    auto n2 = 2;
    REQUIRE(n1 + n2 == add(n1, n2));
}
