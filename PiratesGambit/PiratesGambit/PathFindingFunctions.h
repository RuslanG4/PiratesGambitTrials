#pragma once
#include "BattleGridNode.h"
#include"Includes.h"
#include"Node.h"

template <typename NodeType>
class Compare {
public:
	bool operator()(const std::shared_ptr<NodeType>& a, const std::shared_ptr<NodeType>& b) {
		// Compare based on the total estimated cost (f cost)
		if (a->getNodeData().fCost == b->getNodeData().fCost) {
			// Use h cost as a tiebreaker
			return a->getNodeData().hCost > b->getNodeData().hCost;
		}
		return a->getNodeData().fCost > b->getNodeData().fCost;
	}
};

template <typename NodeType>
class PathFindingFunctions
{
public:
	static PathFindingFunctions& getInstance()
	{
		static PathFindingFunctions instance;
		return instance;
	}

	static std::vector<int> aStarPathFind(const std::vector<std::shared_ptr<NodeType>>& _area, const std::shared_ptr<NodeType>& _start, const std::shared_ptr<BaseNode>& end);
	static std::vector<int> BreathSearchNodes(const std::vector<std::shared_ptr<NodeType>>& _area, const std::shared_ptr<NodeType>& _startNode, int _depth);
	static std::vector<int> BreathSearchEuclydianNodes(const std::vector<std::shared_ptr<NodeType>>& _area, const std::shared_ptr<NodeType>& _startNode, int _depth);
private:
	PathFindingFunctions() = default;

};

#include "PathFinding.inl"  // Include the implementation file
