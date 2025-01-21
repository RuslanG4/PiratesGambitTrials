#pragma once
#include "BattleGridNode.h"
#include"Includes.h"
class PathFindingFunctions
{
public:
	static PathFindingFunctions& getInstance()
	{
		static PathFindingFunctions instance;
		return instance;
	}

	static std::vector<std::shared_ptr<BattleGridNode>> BreathSearchNodes(const std::shared_ptr<BattleGridNode>& _startNode, int _depth);
private:
	PathFindingFunctions() = default;

};

