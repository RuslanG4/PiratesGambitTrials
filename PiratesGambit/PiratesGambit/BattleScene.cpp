#include "BattleScene.h"

void BattleScene::placeUnits()
{
	for(auto& unit: playerRef->getArmy()->getArmy())
	{
		for(auto& node : startArea)
		{
			if(!node->isOccupied())
			{
				unit->placeUnit(node->getMidPoint());
				unit->setCurrentNodeId(node->getID());
				node->updateOccupied(true);
				break; //end loop
			}
		}
	}
	createMoveableArea(playerRef->getArmy()->getArmy()[5]);
}

void BattleScene::update(float _dt)
{
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		unit->update(_dt);
	}
	detectMouse();
	if (move)
	{
		sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - playerRef->getArmy()->getArmy()[5]->getPosition();
		std::cout << Utility::magnitude(distance.x, distance.y)<<"\n";
		if (Utility::magnitude(distance.x, distance.y) < 2)
		{
			currentNodeInPath++;
			if (currentNodeInPath == path.size())
			{
				move = false;
				battleGrid[playerRef->getArmy()->getArmy()[5]->getCurrentNodeId()]->updateOccupied(false);
				playerRef->getArmy()->getArmy()[5]->setCurrentNodeId(path[currentNodeInPath - 1]->getID());
				createMoveableArea(playerRef->getArmy()->getArmy()[5]);
				currentNodeInPath = 0;
				distance = { 0.0,0.0 };

			}
			else {
				distance = path[currentNodeInPath]->getMidPoint() - playerRef->getArmy()->getArmy()[5]->getPosition();
			}
		}
		playerRef->getArmy()->getArmy()[5]->moveUnit(Utility::unitVector2D(distance));
	}
}

void BattleScene::render(sf::RenderWindow& _win) const
{
	_win.setView(_win.getDefaultView());
	for(auto& node: battleGrid)
	{
		_win.draw(*node->debugShape);
		_win.draw(*node->walkableArea);
	}
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		unit->render(_win);
	}
}

void BattleScene::initialiseBattleGrid()
{
	for (int y = 0; y < rowAmount; y++)
	{
		for (int x = 0; x < colAmount; x++)
		{
			NodeData data;
			data.gridX = offset.x + x * nodeSize;
			data.gridY = offset.y + y * nodeSize;
			data.size = nodeSize;
			battleGrid.push_back(std::make_shared<BattleGridNode>(data));
		}
	}
	//Setup id's first
	int max = rowAmount * colAmount;
	for (int i = 0; i < max; i++)
	{
		battleGrid[i]->setID(i);
		addNeighbours(i);
	}
}

void BattleScene::addNeighbours(int _currentNodeId) const
{
	int row = _currentNodeId / colAmount;
	int col = _currentNodeId % colAmount;
	int neighbourIndex = -1;

	if(_currentNodeId ==60)
	{
		int d = 0;
	}

	//This neighbour algoritihim prioritises vertical/hjorizontal then diagonal
	std::array<int, 8> directionOrder
	{
		0,1,2,3,5,6,7,8 //exclude 4 since that is our cell
	};
	for (auto& direction : directionOrder) {

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < rowAmount && n_col >= 0 && n_col < colAmount) {
			neighbourIndex = n_row * colAmount + n_col;
			battleGrid[_currentNodeId]->addNeighbour(battleGrid[neighbourIndex], direction);
		}
	}
}

void BattleScene::createMoveableArea(const std::unique_ptr<PirateUnit>& _unit)
{
	std::queue<std::pair<std::shared_ptr<BattleGridNode>, int>> nodeQueue;

	sf::Vector2f startPos = battleGrid[_unit->getCurrentNodeId()]->getPosition();

	nodeQueue.emplace(battleGrid[_unit->getCurrentNodeId()], 0);
	nodeQueue.front().first->updateTraversed(true);

	walkableNodes.push_back(battleGrid[_unit->getCurrentNodeId()]);

	while (!nodeQueue.empty())
	{
		auto [currentNode, currentDistance] = nodeQueue.front();
		nodeQueue.pop();

		if (currentDistance >= _unit->getSpeed())
			continue;

		auto neighbours = currentNode->getNeighbours();
		for (auto& neighbour : neighbours)
		{
			if (!neighbour.first->hasBeenTraversed() && neighbour.second % 2 != 0)
			{
				neighbour.first->updateTraversed(true);
				int dx = (neighbour.first->getPosition().x - startPos.x) * (neighbour.first->getPosition().x - startPos.x) / nodeSize; //Euclidean Distance, / nodeSize
				int dy = (neighbour.first->getPosition().y - startPos.y) * (neighbour.first->getPosition().y - startPos.y) / nodeSize;
				nodeQueue.emplace(neighbour.first, std::ceil(std::sqrt(dx /64  + dy / nodeSize))); // std::ceil for .5s
				if(!neighbour.first->isOccupied())
				{
					walkableNodes.push_back(neighbour.first);
				}
			}
		}
	}
	for(auto& node : walkableNodes)
	{
		node->walkableArea->setFillColor(sf::Color::Green);
	}
	for(auto & node : battleGrid)
	{
		node->updateTraversed(false);
	}
}

void BattleScene::aStarPathFind(const std::shared_ptr<BattleGridNode>& _start, const std::shared_ptr<BattleGridNode>& end)
{
	std::priority_queue<std::shared_ptr<BattleGridNode>, std::vector<std::shared_ptr<BattleGridNode>>, Compare> nodeQueue;

	nodeQueue.push(_start);
	_start->clearPrevious();
	end->clearPrevious();


	while (!nodeQueue.empty()) {
		std::shared_ptr<BattleGridNode> currentTop = nodeQueue.top();

		nodeQueue.pop();

		if (currentTop == end) { //found
			break;
		}

		if (!currentTop->hasBeenTraversed()) {
			currentTop->updateTraversed(true);

			auto neighbours = currentTop->getNeighbours();

			for (auto& neighbour : neighbours){
				if (!neighbour.first->hasBeenTraversed()) {
					neighbour.first->setPrevious(currentTop);

					neighbour.first->setGCost(currentTop->getNodeData().gCost + 1);
					int dx = (neighbour.first->getPosition().x - end->getPosition().x) * (neighbour.first->getPosition().x - end->getPosition().x) / nodeSize; //Euclidean Distance, / nodeSize
					int dy = (neighbour.first->getPosition().y - end->getPosition().y) * (neighbour.first->getPosition().y - end->getPosition().y) / nodeSize;
					neighbour.first->setHCost(std::ceil(std::sqrt(dx / 64 + dy / nodeSize)));
					neighbour.first->setFCost(neighbour.first->getNodeData().gCost + neighbour.first->getNodeData().hCost);

					nodeQueue.push(neighbour.first);
				}
			}
		}
	}
	createVectors(end);
}

void BattleScene::createVectors(const std::shared_ptr<BattleGridNode>& end)
{
	std::shared_ptr<BattleGridNode> current = end;
	path.clear();
	while(current->getPrevious() != nullptr)
	{
		path.push_back(current);
		current->walkableArea->setFillColor(sf::Color::Red);
		/*int f = current->getID();
		
		sf::Vector2f direction = current->getPosition()-current->getPrevious()->getPosition();
		direction = Utility::unitVector2D(direction);
		current->getPrevious()->setMovementVector(direction);
		*/
		current = current->getPrevious();
	}
	std::reverse(path.begin(), path.end());

	for (auto& node : battleGrid)
	{
		node->updateTraversed(false);
	}
	for(auto& node : walkableNodes)
	{
		node->walkableArea->setFillColor(sf::Color::Transparent);
	}
	walkableNodes.clear();
}

void BattleScene::initialiseStartArea()
{
	for(int y = 0; y < rowAmount; y++)
	{
		for(int x = 0; x < 2; x++)
		{
			int nodeID = y * colAmount + x;
			startArea.push_back(battleGrid[nodeID]);
		}
	}
}

void BattleScene::detectMouse()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	for (auto& node : walkableNodes)
	{
		if (Mouse::getInstance().getHasClicked())
		{
			if (node->walkableArea->getGlobalBounds().contains(mousePos))
			{
				aStarPathFind(battleGrid[playerRef->getArmy()->getArmy()[5]->getCurrentNodeId()], node);
				move = true;
			}
		}
	}
}

void BattleScene::moveUnit(const std::unique_ptr<PirateUnit>& _unit)
{
	
}

int BattleScene::getCurrentNodeID(sf::Vector2f _pos)
{
	int x = static_cast<int>((_pos.x - offset.x) / nodeSize);
	int y = static_cast<int>((_pos.y - offset.y) / nodeSize);
	int currentNode = x + (y * colAmount);

	std::cout << currentNode << "\n";

	return currentNode;
}
