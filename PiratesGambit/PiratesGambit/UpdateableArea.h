#pragma once
#include"Includes.h"
#include"Node.h"

class UpdateableArea
{
public:
	UpdateableArea(){};

	void updateVisibleNodes(const std::shared_ptr<Node>& _startNode, int depth);
	const std::vector<std::shared_ptr<Node>>& getUpdateableNodes() const { return updateArea; }
private:
	std::vector<std::shared_ptr<Node>> updateArea;
};

