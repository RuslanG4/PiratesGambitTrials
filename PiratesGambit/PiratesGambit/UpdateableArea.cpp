#include "UpdateableArea.h"

//searches neighbours of a start node based on the depth and adds them to a set to know which nodes to immediately update
void UpdateableArea::updateVisibleNodes(const std::shared_ptr<Node>& _startNode, int depth)
{
	//debug
	/*for (auto& node : updateArea) {
		if (node != nullptr) {
			node->debugShape->setFillColor(sf::Color::Transparent);
		}
	}*/
	//
	updateArea.clear();

	//determines area, 3x3, 5x5 if depth of 1 then area is 3x3
	int iterations = (1 + 2 * depth) * (1 + 2 * depth);
	int iterCount = 1;

	std::queue<std::shared_ptr<Node>> nodeQueue;
	nodeQueue.push(_startNode);
	updateArea.push_back(_startNode);

	//debug
	_startNode->debugShape->setFillColor(sf::Color(123, 123, 123, 180));

	while (!nodeQueue.empty() && iterCount < iterations) {
		std::shared_ptr<Node> currentNode = nodeQueue.front();
		nodeQueue.pop();

		auto neighbours = currentNode->getNeighbours();
		for (auto& neighbour : neighbours) {
			//add node if it's not already in my area and i haven't reached my limit of iterations of neighbours
			if (std::ranges::find(updateArea.begin(), updateArea.end(), neighbour.first) == updateArea.end() && iterCount < iterations) {

				//debug
				neighbour.first->debugShape->setFillColor(sf::Color(123, 123, 123, 180));

				iterCount++;

				updateArea.push_back(neighbour.first);
				nodeQueue.push(neighbour.first);
			}
		}
	}
}
