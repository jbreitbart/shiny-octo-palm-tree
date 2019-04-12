/*
 *
 * Breadth First Search (BFS)
 *
 */

#pragma once

#include <app/graph.h>

#include <queue>
#include <string>
#include <unordered_set>

#include "app/log.h"

/**
 *
 *  Breadth-first-search (BFS) implementation
 *
 */
class BreadthFirstSearch {

  public:
	/**
	 *
	 * Find a named node.
	 *
	 * This method performs a BFS and returns the first node with
	 * a given identifier.
	 *
	 * @param graph to search.
	 * @param id Identifier to be found.
	 * @return Returns the found node, or null in case no node
	 * has been found.
	 *
	 */
	NodeRef find(const GraphRef &graph, const std::string &id) {
		// empty graph?
		if (graph->getFirst() == nullptr) {
			return nullptr;
		}

		// store all nodes already visited
		std::unordered_set<NodeRef> visited;

		// a copy of the todo queue to allow fast lookup for duplicates
		std::unordered_set<NodeRef> todoSet;

		// todo list
		std::queue<NodeRef> todo;

		// insert first element
		todo.emplace(graph->getFirst());
		todoSet.insert(graph->getFirst());

		while (!todo.empty()) {
			auto work = todo.front();
			logger->debug("working on node {}", work->getId());

			if (work->getId() == id) {
				logger->debug("solution found");
				return work;
			}
			visited.insert(work);

			for (auto &&e : work->getConnections()) {
				if (visited.count(e) == 0 && todoSet.count(e) == 0) {
					todo.emplace(e);
					todoSet.insert(e);
				}
			}

			auto removedElements = todoSet.erase(work);
			assert(removedElements == 1);
			todo.pop();
			assert(todoSet.size() == todo.size());
		}

		logger->debug("no solution found");
		return nullptr;
	}
};
