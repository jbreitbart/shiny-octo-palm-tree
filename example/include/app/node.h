/*
 *
 * Node
 *
 */

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "app/log.h"

class Node;
using NodeRef = Node *;

/**
 *
 * Node
 *
 * This class implements a graph node element.
 *
 */
class Node {
  private:
	const std::string m_id;
	std::vector<NodeRef> m_edges;

  public:
	Node() = delete;
	explicit Node(std::string id) : m_id(std::move(id)) {}

  public:
	/**
	 *
	 * Factory method
	 *
	 * @param id Identifier of node
	 * @return Returns a reference to the created node instance
	 *
	 */
	static NodeRef createInstance(const std::string &id) { return new Node(id); }

  public:
	/**
	 *
	 * Create new node instance and add it as a child node
	 *
	 * @param otherNode Reference to node to connect to
	 *
	 */
	void connect(NodeRef otherNode) {
		if (otherNode == nullptr) {
			logger->error("Invalid input node::connect. Dropping call.");
			return;
		}
		m_edges.emplace_back(otherNode);
	}

	/**
	 *
	 * Get node identifier
	 *
	 * @return Returns the node identifier
	 *
	 */
	std::string getId() const { return m_id; }

	/**
	 *
	 * Get node connections
	 *
	 * @return Returns the connections of the node to other nodes
	 *
	 */
	auto getConnections() const { return m_edges; }

	/**
	 *
	 * Check if the content of nodes are equal
	 *
	 * This function checks if the content (id) of nodes are equal.
	 *
	 * @return Returns true if equal, false otherwise.
	 *
	 */
	bool equals(const NodeRef &node) const { return this->getId() == node->getId(); }
};
