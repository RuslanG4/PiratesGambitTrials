#include "BattleGridNode.h"

void BattleGridNode::addNeighbour(const std::shared_ptr<BattleGridNode>& t_cellId)
{
	m_neighbours.push_back(t_cellId);
}
