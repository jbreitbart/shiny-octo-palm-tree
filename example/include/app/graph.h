/*
 *
 * Graph
 *
 */

#pragma once

#include <app/node.h>

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "app/log.h"

class Graph;
using GraphRef = std::shared_ptr<Graph>;

/**
 *
 * Graph
 *
 * This class implements a graph.
 *
 */
class Graph {
  private:
	// all nodes of the graph
	std::vector<NodeRef> m_nodes;
	// all IDs already present in the graph
	std::unordered_set<std::string> m_IDs;

  public:
	Graph() { clear(); }

	~Graph() {
		for (auto ptr : m_nodes) {
			delete ptr;
		}
	}

  public:
	/**
	 *
	 * Factory method
	 *
	 * @return Returns a reference to the created graph instance
	 *
	 */
	static GraphRef createInstance() { return std::make_shared<Graph>(); }

  public:
	/**
	 *
	 * Create new node instance and add it as a child node
	 *
	 * @param id Identifier of node
	 * @return Returns reference to created node instance
	 *
	 */
	NodeRef addNode(const std::string &id) {
		if (m_IDs.count(id) == 1) {
			logger->error("Trying to add a duplicated ID.");
			return nullptr;
		}

		m_nodes.emplace_back(new Node(id));
		m_IDs.insert(id);

		assert(m_IDs.size() == m_nodes.size());
		return m_nodes.back();
	}

	/**
	 *
	 * Create an edge between two nodes
	 *
	 * @param node1 Reference to node
	 * @param node2 Reference to node
	 *
	 */
	void addEdge(const NodeRef &node1, const NodeRef &node2) {
		// TODO nodes may actually be of a different graph? Should we prevent this?
		if ((node1 == nullptr) || (node2 == nullptr)) {
			logger->error("Invalid input graph::addEdge. Dropping call.");
			return;
		}
		node1->connect(node2);
		node2->connect(node1);
	}

	/**
	 *
	 * Get graph size
	 *
	 * This method returns the graph size as the number of nodes.
	 *
	 * @return Returns the graph size, or zero for an empty graph.
	 *
	 */
	size_t size() const { return m_nodes.size(); }

	/**
	 *
	 * Clear graph
	 *
	 */
	void clear() {
		m_nodes.clear();
		m_IDs.clear();
	}

	/**
	 *
	 * Check if graph is empty
	 *
	 * @return Returns true if the graph is empty, false otherwise.
	 *
	 */
	bool empty() const { return m_nodes.empty(); }

	/**
	 *
	 * Get node with a specific index
	 *
	 * @param index Index of the node to be retrieved.
	 * @return Returns a reference to an existing node of the graph,
	 * or null if the index is out of range.
	 *
	 */
	NodeRef getNode(size_t index) const {
		if (index >= m_nodes.size()) {
			return nullptr;
		}
		return m_nodes.at(index);
	}

	/**
	 *
	 * Get first node of graph (root)
	 *
	 * @return Returns a reference to the first node of the graph,
	 * or null if the graph is empty.
	 *
	 */
	NodeRef getFirst() const {
		if (m_nodes.empty()) {
			return nullptr;
		}
		return m_nodes.front();
	}

	/**
	 * Tests whether a graph contains the given node.
	 */
	bool contains(const NodeRef &node) const {
		return std::find(m_nodes.begin(), m_nodes.end(), node) != m_nodes.end();
	}
};
