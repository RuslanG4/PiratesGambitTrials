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

std::vector<std::shared_ptr<BattleGridNode>> PathFindingFunctions::BreathSearchEuclydianNodes(const std::shared_ptr<BattleGridNode>& _startNode, int _depth)
{
	std::queue<std::pair<std::shared_ptr<BattleGridNode>, int>> nodeQueue;
	std::vector<std::shared_ptr<BattleGridNode>> BreathArea;
	BreathArea.push_back(_startNode);
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
			if (!neighbour.first->hasBeenTraversed() && neighbour.second % 2 != 0)
			{
				neighbour.first->updateTraversed(true);

				float dx = static_cast<float>(neighbour.first->getPosition().x - startPos.x);
				float dy = static_cast<float>(neighbour.first->getPosition().y - startPos.y);

				float distance = std::hypotf(dx / 80, dy / 80);

				nodeQueue.emplace(neighbour.first, std::ceil(distance)); // std::ceil for rounding up

				if (!neighbour.first->isOccupied()) {
					neighbour.first->setAsWalkable();
				}

				BreathArea.push_back(neighbour.first);
			}
		}
	}
	return BreathArea;
}

std::vector<std::shared_ptr<BattleGridNode>> PathFindingFunctions::aStarPathFind(const std::shared_ptr<BattleGridNode>& _start, const std::shared_ptr<BattleGridNode>& end)
{
	std::priority_queue<std::shared_ptr<BattleGridNode>, std::vector<std::shared_ptr<BattleGridNode>>, Compare> nodeQueue;
	std::vector<std::shared_ptr<BattleGridNode>> path;

	nodeQueue.push(_start);
	_start->clearPrevious();
	end->clearPrevious();

	while (!nodeQueue.empty()) {
		std::shared_ptr<BattleGridNode> currentTop = nodeQueue.top();

		nodeQueue.pop();

		if (currentTop == end) { //found
			break;
		}

		if (!currentTop->hasBeenTraversed()) {
			currentTop->updateTraversed(true);

			auto neighbours = currentTop->getNeighbours();

			for (auto& neighbour : neighbours) {
				if (!neighbour.first->hasBeenTraversed() && !neighbour.first->isOccupied()) {
					neighbour.first->setPrevious(currentTop);

					neighbour.first->setGCost(currentTop->getNodeData().gCost + 1);

					float dx = static_cast<float>(neighbour.first->getPosition().x - end->getPosition().x);
					float dy = static_cast<float>(neighbour.first->getPosition().y - end->getPosition().y);

					float hCost = std::hypotf(dx / 80, dy / 80);
					neighbour.first->setHCost(std::ceil(hCost));
					neighbour.first->setFCost(neighbour.first->getNodeData().gCost + neighbour.first->getNodeData().hCost);

					nodeQueue.push(neighbour.first);
				}
			}
		}
	}

	std::shared_ptr<BattleGridNode> current = end;
	while (current->getPrevious() != nullptr)
	{
		path.push_back(current);
		current = current->getPrevious();
	}

	std::ranges::reverse(path.begin(), path.end());

	return path;
}
