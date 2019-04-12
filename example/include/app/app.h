/**
 *
 * Application
 *
 */

#pragma once

#include <app/bfs.h>

#include <chrono>
#include <memory>

#include <cassert>
#include <cstdlib>

#include "app/log.h"

/*
 *
 * TEST PARAMETERS
 *
 * RUN FINAL TEST WITH DEFAULT VALUES.
 *
 */
static const int NUM_DATASET_LEVELS = LEVELS; ///< Depth of the graph (default: 5)
static const int NUM_DATASET_NODES = NODES;   ///< Number of child nodes per node (default: 5)

/**
 *
 * Breadth-First-Search Application
 *
 */
class Application {

  public:
	Application() = default;

  public:
	/**
	 *
	 * Run application
	 *
	 * @return Returns 0 is search was successful, -1 in case of error.
	 *
	 */
	int run() {
		auto bfs = std::make_unique<BreadthFirstSearch>();
		auto graph = createGraph(NUM_DATASET_LEVELS, NUM_DATASET_NODES);
		bool status = performSearch(bfs, graph);

		return (status ? EXIT_SUCCESS : EXIT_FAILURE);
	}

  private:
	/**
	 *
	 * Create child nodes.
	 *
	 * This method recursively creates child nodes of a node.
	 *
	 * @param graph to create childs for
	 * @param parent of the new nodes
	 * @param numNodes Number of child nodes per parent node to create
	 * @param numLevels Depth of the recursion to create child nodes
	 * @param level Internal level counter
	 *
	 * IMPORTANT: This method is not thread-safe!
	 *
	 */
	void createChilds(const GraphRef &graph, const NodeRef &parent, int numNodes, int numLevels, int level) {

		char nameBuffer[64];

		for (int i = 0; i < numNodes; i++) {

			sprintf(nameBuffer, "Node%d", static_cast<int>(graph->size()) - 1);

			auto child = graph->addNode(nameBuffer);

			if (nullptr != parent) {
				graph->addEdge(parent, child);
			}

			if (level < numLevels) {
				createChilds(graph, child, numNodes, numLevels, level + 1);
			}
		}
	}

	/**
	 *
	 * Create dataset
	 *
	 * This method creates a graph with a given depth and given
	 * number of childs per parent node
	 *
	 * @param levels Number of hierarchy levels (depth) of the graph
	 * @param nodes Number of nodes per parent node
	 * @return Returns a reference to the root node of the graph
	 *
	 * IMPORTANT: This method is not thread-safe!
	 *
	 */
	GraphRef createGraph(int levels, int nodes) {

		logger->info("creating dataset...");

		auto graph = std::make_shared<Graph>();

		graph->addNode("root");

		for (int level = 0; level < levels; level++) {
			createChilds(graph, graph->getFirst(), nodes, levels, 0);
		}

		size_t numNodes = graph->size();
		size_t numEdges = 0;

		for (size_t edgeDistance = 2; edgeDistance < numNodes / 2; edgeDistance *= 2) {

			for (size_t index = 0; index < (numNodes - edgeDistance * 2); index += edgeDistance * 2) {
				NodeRef node1 = graph->getNode(index);
				assert(nullptr != node1);

				NodeRef node2 = graph->getNode(index + edgeDistance);
				assert(nullptr != node1);

				graph->addEdge(node1, node2);
				numEdges++;
			}
		}

		logger->info("created dataset with {} nodes, {} cross-level edges", numNodes, numEdges);

		return graph;
	}

	/**
	 *
	 * Perform search
	 *
	 * This method performs multiple breadth-first-searches on a
	 * given graph.
	 *
	 * @param bfs Reference to breadth first search implementation
	 * @param graph Reference to a given graph
	 * @return Returns true if all search operations worked as expected,
	 * false otherwise.
	 *
	 */
	bool performSearch(std::unique_ptr<BreadthFirstSearch> &bfs, const GraphRef &graph) {

		auto absNodeCount = static_cast<int>(graph->size());
		int notFoundNodeCount = 0;

		{
			logger->info("Searching existing...");

			auto tStart = std::chrono::high_resolution_clock::now();

			char nameBuffer[64];

			int percent = -1;

			for (int node = 0; node < absNodeCount; node += 23) {
				sprintf(nameBuffer, "Node%d", node);

				int nextPercent = (((node + 1) * 100) / absNodeCount);
				if (nextPercent != percent) {
					percent = nextPercent;
					logger->debug("{}%", percent);
				}

				if (nullptr == bfs->find(graph, nameBuffer)) {
					logger->debug("not found: {}", nameBuffer);
					bfs->find(graph, nameBuffer);
					notFoundNodeCount++;
				}
			}

			auto tElapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - tStart).count();
			logger->info("Search existing - elapsed time = {:0.3f} seconds", tElapsed);

			if (notFoundNodeCount > 0) {
				logger->error("{} nodes have not been found!", notFoundNodeCount);
				return false;
			}
		}

		{
			logger->info("Searching for non-existing...");

			auto tStart = std::chrono::high_resolution_clock::now();
			auto result = bfs->find(graph, "DOES_NOT_EXIST");
			auto tElapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - tStart).count();

			logger->info("Search for non-existing time = {:0.3f} seconds", tElapsed);
			if (nullptr != result) {
				logger->error("non-existing nodes have been found!");
				return false;
			}
		}

		return true;
	}
};
