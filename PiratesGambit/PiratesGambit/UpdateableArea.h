#pragma once
#include"Includes.h"
#include"Node.h"

class UpdateableArea
{
public:
	UpdateableArea() = default;

	void updateVisibleNodes(Node* _startNode, int depth);
	std::vector<Node*> getUpdateableNodes() const { return updateArea; }
private:
	std::vector<Node*> updateArea;
};

