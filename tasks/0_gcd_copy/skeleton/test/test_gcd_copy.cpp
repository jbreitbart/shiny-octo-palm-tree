#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "lib/gcd.hpp"

TEST_CASE("GCD") { REQUIRE(4 == gcd(4, 12)); }
TEST_CASE("GCD_SWAPPED") { REQUIRE(4 == gcd(12, 4)); }
TEST_CASE("GCD_NEGATIVE") { REQUIRE(-1 == gcd(-100, 25)); }
