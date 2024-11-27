#pragma once

struct NodeData
{
	int m_id;
	int size;

	bool occupied{ false };
	bool traversed{ false };

	int gridX; 
	int gridY; 

	int fCost = 0;
	int gCost = 0;
	int hCost = 0;

};

struct AnimationState
{
    int currentFrame = 0;
    float elapsedTime = 0.0f;
};