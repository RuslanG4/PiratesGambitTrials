#include "PathFindingFunctions.h"

std::vector<std::shared_ptr<BattleGridNode>> PathFindingFunctions::BreathSearchNodes(const std::shared_ptr<BattleGridNode>& _startNode, int _depth)
{
	std::queue<std::pair<std::shared_ptr<BattleGridNode>, int>> nodeQueue;
	std::vector<std::shared_ptr<BattleGridNode>> BreathArea;

	sf::Vector2f startPos = _startNode->getPosition();

	nodeQueue.emplace(_startNode, 0);
	nodeQueue.front().first->updateTraversed(true);

	while (!nodeQueue.empty())
	{
		auto [currentNode, currentDistance] = nodeQueue.front();
		nodeQueue.pop();

		if (currentDistance >= _depth)
			continue;

		auto neighbours = currentNode->getNeighbours();
		for (auto& neighbour : neighbours)
		{
			if (!neighbour.first->hasBeenTraversed())
			{
				neighbour.first->updateTraversed(true);

				float dx = static_cast<float>(neighbour.first->getPosition().x - startPos.x);
				float dy = static_cast<float>(neighbour.first->getPosition().y - startPos.y);

				float distance = std::hypotf(dx / 80, dy / 80); //replace with node size

				nodeQueue.emplace(neighbour.first, std::ceil(distance)); // std::ceil for rounding up

				BreathArea.push_back(neighbour.first);
			}
		}
	}
	for (auto& node : BreathArea)
	{
		node->updateTraversed(false);
	}

	return BreathArea;
}
