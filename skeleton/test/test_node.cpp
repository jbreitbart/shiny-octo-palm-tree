#include "app/log.h"
#include "app/node.h"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Nodes with the same id are equal") {
	auto n1 = Node("Yann");
	auto n2 = Node("Jens");
	auto n3 = Node("Jens");
	REQUIRE(!n1.equals(&n2));
	REQUIRE(n2.equals(&n3));
}
