#include "Node.h"

void Node::addNeighbour(const std::shared_ptr<BaseNode>& t_cellId, int _neighbourPos)
{
    if (auto battleNeighbour = std::dynamic_pointer_cast<Node>(t_cellId)) {
        m_neighbours.emplace_back(battleNeighbour, _neighbourPos);
    }
    else {
        std::cout << "Error wrong node passed in";
    }
}

const std::vector<std::pair<std::shared_ptr<Node>, int>>& Node::getNeighbours()
{
    return m_neighbours;
}

