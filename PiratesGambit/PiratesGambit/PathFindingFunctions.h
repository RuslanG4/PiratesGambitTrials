#pragma once
#include "BattleGridNode.h"
#include"Includes.h"
class PathFindingFunctions
{
public:
	class Compare {
	public:
		bool operator()(const std::shared_ptr<BattleGridNode>& a, const std::shared_ptr<BattleGridNode>& b) {
			// Compare based on the total estimated cost (f cost)
			if (a->getNodeData().fCost == b->getNodeData().fCost) {
				// Use h cost as a tiebreaker
				return a->getNodeData().hCost > b->getNodeData().hCost;
			}
			return a->getNodeData().fCost > b->getNodeData().fCost;
		}
	};


	static PathFindingFunctions& getInstance()
	{
		static PathFindingFunctions instance;
		return instance;
	}

	static std::vector<std::shared_ptr<BattleGridNode>> BreathSearchNodes(const std::shared_ptr<BattleGridNode>& _startNode, int _depth);
	static std::vector<std::shared_ptr<BattleGridNode>> BreathSearchEuclydianNodes(const std::shared_ptr<BattleGridNode>& _startNode, int _depth);
	static std::vector<std::shared_ptr<BattleGridNode>> aStarPathFind(const std::shared_ptr<BattleGridNode>& _start, const std::shared_ptr<BattleGridNode>& end);
private:
	PathFindingFunctions() = default;

};

