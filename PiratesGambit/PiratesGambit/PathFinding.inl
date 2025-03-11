#pragma once

#include "PathFindingFunctions.h"  // Make sure the header is included

template <typename NodeType>
std::vector<std::shared_ptr<NodeType>> PathFindingFunctions<NodeType>::aStarPathFind(
    const std::shared_ptr<NodeType>& _start,
    const std::shared_ptr<NodeType>& end,
	bool isBoatMode)
{
	std::priority_queue<std::shared_ptr<NodeType>, std::vector<std::shared_ptr<NodeType>>, Compare<NodeType>> nodeQueue;
	std::vector<std::shared_ptr<NodeType>> allScannedNodes; //used for then clearing
	std::vector<std::shared_ptr<NodeType>> path;

	nodeQueue.push(_start);
	_start->clearPrevious();
	end->clearPrevious();

	while (!nodeQueue.empty()) {
		std::shared_ptr<NodeType> currentTop = nodeQueue.top();
		
		nodeQueue.pop();

		if (currentTop == end) { //found
			break;
		}

		if (!currentTop->hasBeenTraversed()) {
			currentTop->updateTraversed(true);
			allScannedNodes.push_back(currentTop);

			auto neighbours = currentTop->getNeighbours();

			for (auto& neighbourNode : neighbours) {

					float movementCost = (neighbourNode.second == 1) ? 1.0f : 1.4f; // 1.0 for straight, 1.4 for diagonal
					float newGCost = currentTop->getNodeData().gCost + movementCost;

					bool isValidNode = (!isBoatMode && neighbourNode.first->getIsLand()) ||
						(isBoatMode && !neighbourNode.first->getIsLand());

					if ((!neighbourNode.first->hasBeenTraversed() || newGCost < neighbourNode.first->getNodeData().gCost ) 
						&& !neighbourNode.first->isOccupied()
						&& isValidNode) 
					{
						neighbourNode.first->setPrevious(currentTop);
						neighbourNode.first->setGCost(newGCost);

						float dx = static_cast<float>(neighbourNode.first->getPosition().x - end->getPosition().x);
						float dy = static_cast<float>(neighbourNode.first->getPosition().y - end->getPosition().y);
				
						float hCost = (std::abs(dx) + std::abs(dy)) / _start->getNodeData().size;

						neighbourNode.first->setHCost(hCost);
						neighbourNode.first->setFCost(neighbourNode.first->getNodeData().gCost + neighbourNode.first->getNodeData().hCost);

						nodeQueue.push(neighbourNode.first);
					}
				
			}
		}
	}

	ClearTraversedNodes(allScannedNodes);

	std::shared_ptr<NodeType> current = end;
	while (current->getPrevious() != nullptr)
	{
		path.push_back(current);
		current = std::static_pointer_cast<NodeType>(current->getPrevious());
	}

	std::ranges::reverse(path.begin(), path.end());

	return path;
}

template<typename NodeType>
inline std::vector<std::shared_ptr<NodeType>> PathFindingFunctions<NodeType>::generalAStarPathFind(const std::shared_ptr<NodeType>& _start, const std::shared_ptr<NodeType>& end)
{
	std::priority_queue<std::shared_ptr<NodeType>, std::vector<std::shared_ptr<NodeType>>, Compare<NodeType>> nodeQueue;
	std::vector<std::shared_ptr<NodeType>> allScannedNodes; //used for then clearing
	std::vector<std::shared_ptr<NodeType>> path;

	nodeQueue.push(_start);
	_start->clearPrevious();
	end->clearPrevious();

	while (!nodeQueue.empty()) {
		std::shared_ptr<NodeType> currentTop = nodeQueue.top();

		nodeQueue.pop();

		if (currentTop == end) { //found
			break;
		}

		if (!currentTop->hasBeenTraversed()) {
			currentTop->updateTraversed(true);
			allScannedNodes.push_back(currentTop);

			auto neighbours = currentTop->getNeighbours();

			for (auto& neighbourNode : neighbours) {

				float movementCost = (neighbourNode.second == 1) ? 1.0f : 1.4f; // 1.0 for straight, 1.4 for diagonal
				float newGCost = currentTop->getNodeData().gCost + movementCost;

				if ((!neighbourNode.first->hasBeenTraversed() || newGCost < neighbourNode.first->getNodeData().gCost)
					&& !neighbourNode.first->isOccupied())
				{
					neighbourNode.first->setPrevious(currentTop);
					neighbourNode.first->setGCost(newGCost);

					float dx = static_cast<float>(neighbourNode.first->getPosition().x - end->getPosition().x);
					float dy = static_cast<float>(neighbourNode.first->getPosition().y - end->getPosition().y);

					float hCost = (std::abs(dx) + std::abs(dy)) / _start->getNodeData().size;

					neighbourNode.first->setHCost(hCost);
					neighbourNode.first->setFCost(neighbourNode.first->getNodeData().gCost + neighbourNode.first->getNodeData().hCost);

					nodeQueue.push(neighbourNode.first);
				}

			}
		}
	}

	ClearTraversedNodes(allScannedNodes);

	std::shared_ptr<NodeType> current = end;
	while (current->getPrevious() != nullptr)
	{
		path.push_back(current);
		current = std::static_pointer_cast<NodeType>(current->getPrevious());
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
	std::vector<std::shared_ptr<NodeType>> allScannedNodes; //used for then clearing

	sf::Vector2f startPos = _startNode->getPosition();

	nodeQueue.emplace(_startNode, 0);
	nodeQueue.front().first->updateTraversed(true);

	allScannedNodes.push_back(_startNode);

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
				allScannedNodes.push_back(_area[neighbourID.first]);

				float dx = static_cast<float>(_area[neighbourID.first]->getPosition().x - startPos.x);
				float dy = static_cast<float>(_area[neighbourID.first]->getPosition().y - startPos.y);

				float distance = std::hypotf(dx / 80, dy / 80); //replace with node size

				nodeQueue.emplace(_area[neighbourID.first], std::ceil(distance)); // std::ceil for rounding up

				BreathArea.push_back(neighbourID.first);
			}
		}
	}

	ClearTraversedNodes(allScannedNodes);

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
	std::vector<std::shared_ptr<NodeType>> allScannedNodes; //used for then clearing

	BreathArea.push_back(_startNode->getID());
	sf::Vector2f startPos = _startNode->getPosition();

	nodeQueue.emplace(_startNode, 0);
	nodeQueue.front().first->updateTraversed(true);
	allScannedNodes.push_back(_startNode);

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
				allScannedNodes.push_back(_area[neighbourID.first]);

				float dx = static_cast<float>(_area[neighbourID.first]->getPosition().x - startPos.x);
				float dy = static_cast<float>(_area[neighbourID.first]->getPosition().y - startPos.y);

				float distance = std::hypotf(dx / 80, dy / 80);

				nodeQueue.emplace(_area[neighbourID.first], std::ceil(distance)); // std::ceil for rounding up

				BreathArea.push_back(neighbourID.first);
			}
		}
	}

	ClearTraversedNodes(allScannedNodes);

	return BreathArea;
}

template<typename NodeType>
inline std::vector<std::shared_ptr<NodeType>> PathFindingFunctions<NodeType>::BreathSearchEuclydianIslands(const std::shared_ptr<NodeType>& _startNode, int _depth)
{
	std::queue<std::pair<std::shared_ptr<NodeType>, int>> nodeQueue;
	std::vector<std::shared_ptr<NodeType>> BreathArea;
	std::vector<std::shared_ptr<NodeType>> allScannedNodes; //used for then clearing

	BreathArea.push_back(_startNode);
	sf::Vector2f startPos = _startNode->getPosition();

	nodeQueue.emplace(_startNode, 0);
	nodeQueue.front().first->updateTraversed(true);
	allScannedNodes.push_back(_startNode);

	while (!nodeQueue.empty())
	{
		auto [currentNode, currentDistance] = nodeQueue.front();
		nodeQueue.pop();

		if (currentDistance >= _depth)
			continue;

		auto neighbours = currentNode->getNeighbours();
		for (auto& neighbour : neighbours)
		{
			if (!neighbour.first->hasBeenTraversed() && neighbour.second % 2 != 0 && neighbour.first->getParentTileType() == LAND && !neighbour.first->IsInBuildingArea())
			{
				if(neighbour.first->isOccupied())
					continue;
				neighbour.first->updateTraversed(true);
				allScannedNodes.push_back(neighbour.first);

				float dx = static_cast<float>(neighbour.first->getPosition().x - startPos.x);
				float dy = static_cast<float>(neighbour.first->getPosition().y - startPos.y);

				float distance = std::hypotf(dx / 32, dy / 32);

				nodeQueue.emplace(neighbour.first, std::ceil(distance)); // std::ceil for rounding up

				BreathArea.push_back(neighbour.first);
			}
		}
	}
	ClearTraversedNodes(allScannedNodes);

	return BreathArea;
}

template<typename NodeType>
inline void PathFindingFunctions<NodeType>::ClearTraversedNodes(const std::vector<std::shared_ptr<NodeType>>& _searchedNodes)
{
	for(auto& node : _searchedNodes)
	{
		node->updateTraversed(false);
	}
}

