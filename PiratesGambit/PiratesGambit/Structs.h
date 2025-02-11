#pragma once

struct NodeData
{
	int m_id;
	int size;

	bool occupied{ false };
	bool traversed{ false };

	int gridX; 
	int gridY; 

	float fCost = 0;
	float gCost = 0;
	float hCost = 0;

	std::vector<std::pair<int, int>> neighbourIDs;
};

struct AnimationState
{
    int currentFrame = 0;
    float elapsedTime = 0.0f;
};