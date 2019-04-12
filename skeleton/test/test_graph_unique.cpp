#include "app/graph.h"
#include "app/log.h"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Test graph add - drop duplicated nodes") {
	auto graph = Graph::createInstance();
	auto node = std::make_shared<Node>("Yann");
	graph->addNode(node->getId());
	graph->addNode(node->getId());
	// Check if node ID is unique within a graph
	REQUIRE(graph->size() == 1);
}
