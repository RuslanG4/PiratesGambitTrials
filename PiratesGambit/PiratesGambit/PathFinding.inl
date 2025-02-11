#pragma once

#include "PathFindingFunctions.h"  // Make sure the header is included

template <typename NodeType>
std::vector<int> PathFindingFunctions<NodeType>::aStarPathFind(
    const std::vector<std::shared_ptr<NodeType>>& _area,
    const std::shared_ptr<NodeType>& _start,
    const std::shared_ptr<BaseNode>& end)
{
	std::priority_queue<std::shared_ptr<NodeType>, std::vector<std::shared_ptr<NodeType>>, Compare<NodeType>> nodeQueue;
	std::vector<int> path;
	std::cout << "start" << _start->getID()<<"\n";
	std::cout << "end" << end->getID() << "\n";
	nodeQueue.push(_start);
	_start->clearPrevious();
	end->clearPrevious();

	while (!nodeQueue.empty()) {
		std::shared_ptr<NodeType> currentTop = nodeQueue.top();
		std::cout << "searched" << currentTop->getID()<<"\n";
		nodeQueue.pop();

		if (currentTop == end) { //found
			break;
		}

		if (!currentTop->hasBeenTraversed()) {
			currentTop->updateTraversed(true);

			auto neighbours = currentTop->getNodeData().neighbourIDs;

			for (auto& neighbourID : neighbours) {
				auto it = std::ranges::find_if(_area, [&neighbourID](const std::shared_ptr<NodeType>& node) {
					return node->getID() == neighbourID.first; // Match by ID
					});

				// If a matching node is found
				if (it != _area.end()) {
					auto& neighbourNode = *it;

					float movementCost = (neighbourID.second == 1) ? 1.0f : 1.4f; // 1.0 for straight, 1.4 for diagonal
					float newGCost = currentTop->getNodeData().gCost + movementCost;


					if ((!neighbourNode->hasBeenTraversed() || newGCost < neighbourNode->getNodeData().gCost ) && !neighbourNode->isOccupied()) {
						neighbourNode->setPrevious(currentTop);
						neighbourNode->setGCost(newGCost);

						// Calculate the heuristic (keep division by 80)
						float dx = static_cast<float>(neighbourNode->getPosition().x - end->getPosition().x);
						float dy = static_cast<float>(neighbourNode->getPosition().y - end->getPosition().y);
				
						float hCost = (std::abs(dx) + std::abs(dy)) / _start->getNodeData().size;

						neighbourNode->setHCost(hCost);
						neighbourNode->setFCost(neighbourNode->getNodeData().gCost + neighbourNode->getNodeData().hCost);

						nodeQueue.push(neighbourNode);
					}
				}
			}
		}
	}

	std::shared_ptr<BaseNode> current = end;
	while (current->getPrevious() != nullptr)
	{
		path.push_back(current->getID());
		current = current->getPrevious();  // Ensure this is allowed with const
	}


	std::ranges::reverse(path.begin(), path.end());

	return path;
}

template <typename NodeType>
std::vector<int> PathFindingFunctions<NodeType>::BreathSearchNodes(
	const std::vector<std::shared_ptr<NodeType>>& _area,
	const std::shared_ptr<NodeType>& _startNode,
	int _depth)
{
	std::queue<std::pair<std::shared_ptr<NodeType>, int>> nodeQueue;
	std::vector<int> BreathArea;

	sf::Vector2f startPos = _startNode->getPosition();

	nodeQueue.emplace(_startNode, 0);
	nodeQueue.front().first->updateTraversed(true);

	while (!nodeQueue.empty())
	{
		auto [currentNode, currentDistance] = nodeQueue.front();
		nodeQueue.pop();

		if (currentDistance >= _depth)
			continue;

		auto neighbours = currentNode->getNodeData().neighbourIDs;
		for (auto& neighbourID : neighbours)
		{
			if (!_area[neighbourID.first]->hasBeenTraversed())
			{
				_area[neighbourID.first]->updateTraversed(true);

				float dx = static_cast<float>(_area[neighbourID.first]->getPosition().x - startPos.x);
				float dy = static_cast<float>(_area[neighbourID.first]->getPosition().y - startPos.y);

				float distance = std::hypotf(dx / 80, dy / 80); //replace with node size

				nodeQueue.emplace(_area[neighbourID.first], std::ceil(distance)); // std::ceil for rounding up

				BreathArea.push_back(neighbourID.first);
			}
		}
	}

	return BreathArea;
}

template <typename NodeType>
std::vector<int> PathFindingFunctions<NodeType>::BreathSearchEuclydianNodes(
	const std::vector<std::shared_ptr<NodeType>>& _area,
	const std::shared_ptr<NodeType>& _startNode,
	int _depth)
{
	std::queue<std::pair<std::shared_ptr<NodeType>, int>> nodeQueue;
	std::vector<int> BreathArea;
	BreathArea.push_back(_startNode->getID());
	sf::Vector2f startPos = _startNode->getPosition();

	nodeQueue.emplace(_startNode, 0);
	nodeQueue.front().first->updateTraversed(true);

	while (!nodeQueue.empty())
	{
		auto [currentNode, currentDistance] = nodeQueue.front();
		nodeQueue.pop();

		if (currentDistance >= _depth)
			continue;

		auto neighbours = currentNode->getNodeData().neighbourIDs;
		for (auto& neighbourID : neighbours)
		{
			if (!_area[neighbourID.first]->hasBeenTraversed() && neighbourID.second % 2 != 0)
			{
				_area[neighbourID.first]->updateTraversed(true);

				float dx = static_cast<float>(_area[neighbourID.first]->getPosition().x - startPos.x);
				float dy = static_cast<float>(_area[neighbourID.first]->getPosition().y - startPos.y);

				float distance = std::hypotf(dx / 80, dy / 80);

				nodeQueue.emplace(_area[neighbourID.first], std::ceil(distance)); // std::ceil for rounding up

				BreathArea.push_back(neighbourID.first);
			}
		}
	}
	return BreathArea;
}

