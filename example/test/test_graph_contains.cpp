#include "app/graph.h"
#include "app/log.h"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Test graph contains") {
	auto graph = Graph::createInstance();
	auto node = Node("Bee");

	// Check if graph contains the created node
	REQUIRE_FALSE(graph->contains(&node));

	graph->addNode(node.getId());
	REQUIRE(graph->contains(graph->getFirst()));
}
