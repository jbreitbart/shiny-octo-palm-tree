#include "app/bfs.h"
#include "app/graph.h"
#include "app/log.h"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Test bfs on empty graph") {
	// create BFS object
	auto bfs = std::make_unique<BreadthFirstSearch>();
	REQUIRE(nullptr != bfs);

	// create graph
	auto graph = Graph::createInstance();
	REQUIRE(nullptr != graph);

	// check if H cannot be found from root
	auto result = bfs->find(graph, "H");
	REQUIRE(nullptr == result);
}
