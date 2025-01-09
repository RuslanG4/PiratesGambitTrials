#include "BattleScene.h"

void BattleScene::placeUnits(const std::unique_ptr<Army>& _army, bool _isEnemy) const
{
	auto area = _isEnemy ? enemyStartArea : startArea;
	for(auto& unit: _army->getArmy())
	{
		tacticsArmyUI->initiativeSystem.addUnit(unit);
		for(auto& node : area)
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
}

void BattleScene::update(float _dt)
{
	switch (currentState)
	{
	case PREP:
		UIInterface->update();
		break;
	case BATTLE:
		if (move)
		{
			moveUnit();
		}
		if (currentSelectedUnit->currentState == IDLE && !newAreaSet) {
			tacticsArmyUI->UpdateToInitiativeView(); //update initiative bar
			currentSelectedUnit = tacticsArmyUI->initiativeSystem.getNextUnit();
			createMoveableArea(currentSelectedUnit);
		}
		break;
	case END:
		break;
	}
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		unit->update(_dt);
	}
	for (auto& unit : enemyRef->getArmy()->getArmy())
	{
		unit->update(_dt);
	}
	detectMouse();
	
}

void BattleScene::render(sf::RenderWindow& _win) const
{
	_win.setView(_win.getDefaultView());
	for(auto& node: battleGrid)
	{
		_win.draw(*node->walkableArea);
		_win.draw(*node->debugShape);
	}
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		unit->render(_win);
	}
	for (auto& unit : enemyRef->getArmy()->getArmy())
	{
		unit->render(_win);
	}
	if(canAttack)
	{
		_win.draw(attackIcon);
	}
	tacticsArmyUI->render(_win);
	
	UIInterface->render(_win);
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

void BattleScene::createMoveableArea(const std::shared_ptr<PirateUnit>& _unit)
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
				nodeQueue.emplace(neighbour.first, std::ceil(std::sqrt(dx /nodeSize  + dy / nodeSize))); // std::ceil for .5s
				if(!neighbour.first->isOccupied())
				{
					neighbour.first->setAsWalkable();
				}
				walkableNodes.push_back(neighbour.first);
			}
		}
	}
	for(auto & node : battleGrid)
	{
		node->updateTraversed(false);
	}
	newAreaSet = true;
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
				if (!neighbour.first->hasBeenTraversed() && !neighbour.first->isOccupied()) {
					neighbour.first->setPrevious(currentTop);

					neighbour.first->setGCost(currentTop->getNodeData().gCost + 1);
					int dx = (neighbour.first->getPosition().x - end->getPosition().x) * (neighbour.first->getPosition().x - end->getPosition().x) / nodeSize; //Euclidean Distance, / nodeSize
					int dy = (neighbour.first->getPosition().y - end->getPosition().y) * (neighbour.first->getPosition().y - end->getPosition().y) / nodeSize;
					neighbour.first->setHCost(std::ceil(std::sqrt(dx / nodeSize + dy / nodeSize)));
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
		current = current->getPrevious();
	}
	std::reverse(path.begin(), path.end());

	for (auto& node : battleGrid)
	{
		node->updateTraversed(false);
	}
	for(auto& node : walkableNodes)
	{
		node->setTransparent();
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
			battleGrid[nodeID]->setAsWalkable();
			startArea.push_back(battleGrid[nodeID]);
		}
	}

	for (int y = 0; y < rowAmount; y++)
	{
		for (int x = colAmount-2; x < colAmount; x++)
		{
			int nodeID = y * colAmount + x;
			enemyStartArea.push_back(battleGrid[nodeID]);
		}
	}

}

void BattleScene::detectMouse()
{
	if (Mouse::getInstance().LeftClicked())
	{
		if (UIInterface->UIPressed() && currentState == PREP)
		{
			currentState = BATTLE;
			placeUnits(enemyRef->getArmy(), true);
			tacticsArmyUI->extend();
			currentSelectedUnit = tacticsArmyUI->initiativeSystem.getNextUnit();
			UIInterface->updateModeString("Battle Mode");
			clearStartArea();
			createMoveableArea(currentSelectedUnit);
		}
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
		switch (currentState)
		{
		case PREP:
			UIInterface->update();
			preGameStartUpPlacement(mousePos);
			break;
		case BATTLE:
				for (auto& node : walkableNodes) {
					if(attackNode != -1)
					{
						aStarPathFind(battleGrid[currentSelectedUnit->getCurrentNodeId()], battleGrid[attackNode]);
						move = true;
						canAttack = false;
					}
					else if (node->debugShape->getGlobalBounds().contains(mousePos) && !move)
					{
						aStarPathFind(battleGrid[currentSelectedUnit->getCurrentNodeId()], node);
						move = true;
						canAttack = false;
					}
				}
			break;
		case END:
			break;
		}
	}
	else if (Mouse::getInstance().RightClicked())
	{
		
	}
	else
	{
		if (!move && currentState == BATTLE) {
			hoverMouseOnNode();
		}
		if (currentSelectedUnit && currentState ==PREP) {
			currentSelectedUnit = nullptr;
		}
	}
}

void BattleScene::hoverMouseOnNode()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	for(auto& node : battleGrid)
	{
		if(node->walkableArea->getGlobalBounds().contains(mousePos))
		{
			currentHoverNodeID = node->getID();
			if(isNodeInRangeOfUnit())
			{
				canAttack = true;
				pinpointMousePosition(mousePos, node);
			}else
			{
				canAttack = false;
				attackNode = -1;
				attackIcon.setPosition(sf::Vector2f(-200,-200)); //offscreen
			}

		}
	}
}

void BattleScene::pinpointMousePosition(sf::Vector2f _mousePos, const std::shared_ptr<BattleGridNode>& _currentNode)
{
	float relativeX = _mousePos.x - _currentNode->getPosition().x;
	float relativeY = _mousePos.y - _currentNode->getPosition().y;

	float subNodeWidth = nodeSize / 3;
	float subNodeHeight = nodeSize / 3;

	int gridX = static_cast<int>(relativeX / subNodeWidth);
	int gridY = static_cast<int>(relativeY / subNodeHeight);

	int subNodeIndex = gridY * 3 + gridX + 1;

	adjustAttackIcon(subNodeIndex);
}

void BattleScene::adjustAttackIcon(int _pinPointID)
{
	int nodeID = -1;
	switch (_pinPointID)
	{
	case 1:
		// Top Left
		nodeID = currentHoverNodeID - colAmount - 1;
		break;
	case 2:
		// Top Middle
		nodeID = currentHoverNodeID - colAmount;
		break;
	case 3:
		// Top Right
		nodeID = currentHoverNodeID - colAmount + 1;
		break;
	case 4:
		// Middle Left
		nodeID = currentHoverNodeID - 1;
		break;
	case 5:
		// keep last
		break;
	case 6:
		// Middle Right
		nodeID = currentHoverNodeID + 1;
		break;
	case 7:
		// Bottom Left
		nodeID = currentHoverNodeID + colAmount - 1;
		break;
	case 8:
		// Bottom Middle
		nodeID = currentHoverNodeID + colAmount;
		break;
	case 9:
		// Bottom Right
		nodeID = currentHoverNodeID + colAmount + 1;
		break;
	}
	if (nodeID >= 0 && nodeID < rowAmount * colAmount) {
		auto it = std::ranges::find_if(walkableNodes,
			[nodeID](const auto& node) {
				return node->getID() == nodeID;
			});

		if (it != walkableNodes.end() && !battleGrid[nodeID]->isOccupied()) {
			if (!battleGrid[nodeID]->isOccupied()) {
				attackNode = nodeID;
				attackIcon.setPosition(battleGrid[nodeID]->getMidPoint());
			}
		}
		else
		//Puts icon on first neighbour of unit to attack if on edge of area
		{
			for (auto& node : battleGrid[currentHoverNodeID]->getNeighbours()) {
				if (std::find(walkableNodes.begin(), walkableNodes.end(), node.first) != walkableNodes.end()) {
					attackNode = node.first->getID();
					attackIcon.setPosition(node.first->getMidPoint());
					break;
				}
			}
		}

	}
}

bool BattleScene::isNodeInRangeOfUnit()
{
	for (auto& unit : enemyRef->getArmy()->getArmy())
	{
		for (auto& node : battleGrid[unit->getCurrentNodeId()]->getNeighbours()) {
			if (std::find(walkableNodes.begin(), walkableNodes.end(), node.first) != walkableNodes.end()) {
				if (!node.first->isOccupied() && currentHoverNodeID == battleGrid[unit->getCurrentNodeId()]->getID()) {
					return true;
				}
			}
		}
	}
	return false;
}

void BattleScene::moveUnit()
{
	sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - currentSelectedUnit->getPosition();
	std::cout << Utility::magnitude(distance.x, distance.y) << "\n";
	if (Utility::magnitude(distance.x, distance.y) < 2)
	{
		currentNodeInPath++;
		if (currentNodeInPath == path.size())
		{
			//animate attack
			if (attackNode != -1) {
				currentSelectedUnit->Attack();
			}
			move = false;
			battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateOccupied(false);
			currentSelectedUnit->setCurrentNodeId(path[currentNodeInPath - 1]->getID());
			battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateOccupied(true);
			currentNodeInPath = 0;
			distance = { 0.0,0.0 };
			newAreaSet = false;
		}
		else {
			distance = path[currentNodeInPath]->getMidPoint() - currentSelectedUnit->getPosition();
		}
	}
	currentSelectedUnit->moveUnit(Utility::unitVector2D(distance));
}

void BattleScene::preGameStartUpPlacement(sf::Vector2f _mousePos)
{
	if (currentSelectedUnit == nullptr) {
		currentSelectedUnit = selectUnit(_mousePos);
	}else
	{
		for (auto& node : startArea)
		{
			if (node->debugShape->getGlobalBounds().contains(_mousePos)) {
				if (!node->isOccupied()) {
					battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateOccupied(false);
					currentSelectedUnit->placeUnit(node->getMidPoint());
					node->updateOccupied(true);
					currentSelectedUnit->setCurrentNodeId(node->getID());
					break;
				}
			}
		}
	}
}

void BattleScene::clearStartArea()
{
	for(auto& node : startArea)
	{
		node->setTransparent();
	}
	startArea.clear();
}

std::shared_ptr<PirateUnit> BattleScene::selectUnit(sf::Vector2f _mousePos)
{
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		if (unit->getGlobalBounds().contains(_mousePos))
		{
			oldPositionRef = getCurrentNodeID(_mousePos);
			return unit;
		}
	}
	return nullptr;
}

int BattleScene::getCurrentNodeID(sf::Vector2f _pos)
{
	int x = static_cast<int>((_pos.x - offset.x) / nodeSize);
	int y = static_cast<int>((_pos.y - offset.y) / nodeSize);
	int currentNode = x + (y * colAmount);

	std::cout << currentNode << "\n";

	return currentNode;
}
