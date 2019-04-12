#include "app/bfs.h"
#include "app/graph.h"
#include "app/log.h"
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Test small bfs test") {
	// create BFS object
	auto bfs = std::make_unique<BreadthFirstSearch>();
	REQUIRE(nullptr != bfs);

	// create graph
	auto graph = Graph::createInstance();
	REQUIRE(nullptr != graph);

	// check if everything is clean at the beginning
	REQUIRE(graph->empty());
	REQUIRE(graph->size() == 0);
	REQUIRE(nullptr == graph->getNode(0));
	REQUIRE(nullptr == graph->getFirst());

	// add nodes
	auto a = graph->addNode("A");
	auto b = graph->addNode("B");
	auto c = graph->addNode("C");
	auto d = graph->addNode("D");
	auto e = graph->addNode("E");
	auto f = graph->addNode("F");
	auto g = graph->addNode("G");
	auto h = graph->addNode("H");

	// check if the graph is filled
	REQUIRE(!graph->empty());
	REQUIRE(graph->size() == 8);

	auto graphFirst = graph->getFirst();			// get first element
	REQUIRE(nullptr != graphFirst);					// found an element
	REQUIRE(0 == graphFirst->getId().compare("A")); // really element "A"
	auto graph0 = graph->getNode(0);				// get element 0
	REQUIRE(nullptr != graph0);						// found an element
	REQUIRE(0 == graph0->getId().compare("A"));		// really element "A"
	REQUIRE(graphFirst == graph0);					// point to the same object

	graph->addEdge(a, d);					  // add edges ...
	REQUIRE(a->getConnections().size() == 1); // ... and check connections
	REQUIRE(d->getConnections().size() == 1);

	graph->addEdge(a, e);
	REQUIRE(a->getConnections().size() == 2);
	REQUIRE(e->getConnections().size() == 1);

	graph->addEdge(c, f);
	REQUIRE(c->getConnections().size() == 1);
	REQUIRE(f->getConnections().size() == 1);

	graph->addEdge(c, g);
	REQUIRE(c->getConnections().size() == 2);
	REQUIRE(g->getConnections().size() == 1);

	graph->addEdge(e, h);
	REQUIRE(e->getConnections().size() == 2);
	REQUIRE(h->getConnections().size() == 1);

	graph->addEdge(a, g);
	REQUIRE(a->getConnections().size() == 3);
	REQUIRE(g->getConnections().size() == 2);

	graph->addEdge(f, e);
	REQUIRE(f->getConnections().size() == 2);
	REQUIRE(e->getConnections().size() == 3);

	graph->addEdge(b, g);
	REQUIRE(b->getConnections().size() == 1);
	REQUIRE(g->getConnections().size() == 3);

	// check if node is found
	auto result = bfs->find(graph, "H");
	REQUIRE(nullptr != result);

	// check if found node is the correct one
	if (nullptr != result) {
		REQUIRE(0 == h->getId().compare(result->getId()));
	}

	// check if non-existing node is not found
	REQUIRE(nullptr == bfs->find(graph, "DOES_NOT_EXIST"));

	// check cleanup
	graph->clear();
	REQUIRE(graph->empty());
	REQUIRE(graph->size() == 0);
	REQUIRE(nullptr == graph->getNode(0));
	REQUIRE(nullptr == graph->getFirst());
}
