#include "Node.h"

void Node::addNeighbour(const std::shared_ptr<Node>& t_cellId)
{
	m_neighbours.push_back(t_cellId);
}





