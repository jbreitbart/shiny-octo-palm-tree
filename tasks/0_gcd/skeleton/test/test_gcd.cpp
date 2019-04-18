#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "lib/gcd.hpp"

TEST_CASE("GCD") { REQUIRE(4 == gcd(4, 12)); }
