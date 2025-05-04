#include "BattleScene.h"


void BattleScene::endBattle()
{
	clearArea(walkableNodesIDs);
}

void BattleScene::resetBattle()
{
	for (auto& node : battleGrid)
	{
		node->updateOccupied(false);
	}
	
	showEndGame = false;
	initialiseBattleGrid();
	initialiseStartArea();

	tacticsArmyUI.reset();
	tacticsArmyUI = std::make_unique<TacticsArmyUI>(playerRef->getArmy());
	
	placeUnits(playerRef->getArmy(), false);

	endBattleUI.reset();
	endBattleUI = std::make_unique<EndBattleUI>();

	playerArmyDead->clearArmy();
	enemyArmyDead->clearArmy();

	currentState = PREP;
}

void BattleScene::handleEvent(const sf::Event& event)
{
	endBattleUI->HandleInput(event);
}

void BattleScene::placeUnits(const std::unique_ptr<Army>& _army, bool _isEnemy)
{
	auto area = _isEnemy ? enemyStartArea : startArea;
	for(auto& unit: _army->getArmy())
	{
		tacticsArmyUI->initiativeSystem.addUnit(unit);
		if(_isEnemy)
		{
			auto node = placeEnemyUnits(area, unit);
			node->updateOccupied(true);
			node->updateAllegiance(unit->unitInformation.allegiance);
		}else
		{
			for (auto& node : area)
			{
				if (!node->isOccupied())
				{
					unit->placeUnit(node->getMidPoint());
					unit->setCurrentNodeId(node->getID());
					node->updateOccupied(true);
					node->updateAllegiance(unit->unitInformation.allegiance);
					break; //end loop
				}
			}
		}
	}
}

 std::shared_ptr<BattleGridNode> BattleScene::placeEnemyUnits(std::vector<std::shared_ptr<BattleGridNode>>& _gridArea,
	const std::shared_ptr<PirateUnit>& _unit
)
{
	bool frontLine = false;
	if(_unit->unitInformation.unitType == MELEE)
	{
		frontLine = true;
	}else
	{
		frontLine = false;
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(_gridArea.begin(), _gridArea.end(), g);

	for (auto& node : _gridArea)
	{
		if (!node->isOccupied())
		{
			if(frontLine && node->getID() % 2 == 0)
			{
				_unit->placeUnit(node->getMidPoint());
				_unit->setCurrentNodeId(node->getID());
				return node;
			}
			if (!frontLine && node->getID() % 2 != 0)
			{
				_unit->placeUnit(node->getMidPoint());
				_unit->setCurrentNodeId(node->getID());
				return node;
			}
		}
	}
	return nullptr;
}

void BattleScene::update(float _dt)
{
	tacticsArmyUI->update();
	UIInterface->update();
	switch (currentState) {
	case PREP:
		break;

	case BATTLE:
		if (move) {
			moveUnit();
		}
		if(startEnemyTurnTimer)
		{
			WaitForTurn();
		}
		else {
			if (currentSelectedUnit->unitInformation.unitType == RANGED)
			{
				if (projectileCollisionCheck()) {
					ParticleManager::getInstance().CreateBloodParticle(currentDefendingUnit->getPosition());
					calculateDamage(currentSelectedUnit, currentDefendingUnit); // Damage calculation
					finalizeMoveUnit();
				}
			}
		}
		break;
	case END:
		WaitForEndGameTimer();
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
	for (auto& number : floatingNumbers)
	{
		if (number->isMarkedForDelete())
		{
			floatingNumbers.erase(std::remove(floatingNumbers.begin(), floatingNumbers.end(), number), floatingNumbers.end());
			break;
		}
		number->update(_dt);
	}
	detectMouse();

	if (tacticsArmyUI->animateSlots) {
		tacticsArmyUI->AnimateInitiativeBar(_dt);
	} if (tacticsArmyUI->animateRemoveUnit) {
		tacticsArmyUI->AnimateRemoveUnit(_dt);
	}
}

void BattleScene::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->setView(window->getDefaultView());
	window->draw(background);
	for(auto& node: battleGrid)
	{
		window->draw(*node->walkableArea);
		window->draw(*node->debugShape);
	}
	for (auto& unit : playerRef->getArmy()->getArmy())
	{
		unit->render(window);
	}
	for (auto& unit : enemyRef->getArmy()->getArmy())
	{
		unit->render(window);
	}
	if(canAttack && currentSelectedUnit && currentSelectedUnit->unitInformation.allegiance == HUMAN_PLAYER)
	{
		window->draw(attackIcon);
	}
	tacticsArmyUI->render(window);
	
	UIInterface->render(window);

	for (auto& number : floatingNumbers)
	{
		number->render(window);
	}

	if(showEndGame)
		endBattleUI->Render(window);
}

bool BattleScene::updateNextTurn()
{
	Mouse::getInstance().SetToDefault();
	//update initiative
	if (tacticsArmyUI->finsihedAnimation) {
		tacticsArmyUI->finsihedAnimation = false;
		tacticsArmyUI->animateSlots = false;
		tacticsArmyUI->UpdateToInitiativeView();

		//set next unit
		if (!startUnit) {

			currentSelectedUnit = tacticsArmyUI->initiativeSystem.getNextUnit();
		}
		else {
			startUnit = false;
			tacticsArmyUI->initiativeSystem.getNextUnit();
		}
		createMoveableArea(currentSelectedUnit);

		if (currentSelectedUnit->unitInformation.allegiance != HUMAN_PLAYER) {
			if (!CheckBattleOver(playerRef->getArmy()))
				EnemyTurn();
			else
				clearArea(walkableNodesIDs);
		}
		else {
			CheckBattleOver(enemyRef->getArmy());
		}
		return true;
	}	
	return false;
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
			battleGrid[_currentNodeId]->getNodeData().neighbourIDs.emplace_back(neighbourIndex, direction);
		}
	}
}

void BattleScene::createMoveableArea(const std::shared_ptr<PirateUnit>& _unit)
{
	walkableNodesIDs = PathFindingFunctions<BattleGridNode>::BreathSearchEuclydianNodes(battleGrid ,battleGrid[_unit->getCurrentNodeId()], _unit->getSpeed());
	for (auto& ID : walkableNodesIDs)
	{
		battleGrid[ID]->setAsWalkable();
	}
	newAreaSet = true;
	canAttack = true;
}

void BattleScene::aStarPathFind(const std::shared_ptr<BattleGridNode>& _start, const std::shared_ptr<BattleGridNode>& end)
{
	path = PathFindingFunctions<BattleGridNode>::aStarPathFind(_start, end, false);
	clearArea(walkableNodesIDs);
}

bool BattleScene::projectileCollisionCheck()
{
	auto& projectiles = BulletFactory::getInstance().GetProjectiles();

	for (auto it = projectiles.begin(); it != projectiles.end(); )
	{
		if ((*it)->getBounds().intersects(currentDefendingUnit->getGlobalBounds()))
		{
			it = projectiles.erase(it);
			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
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
		if (UIInterface->UIAttackPressed() && currentState == PREP)
		{
			currentState = BATTLE;
			placeUnits(enemyRef->getArmy(), true);
			tacticsArmyUI->extend();
			currentSelectedUnit = tacticsArmyUI->initiativeSystem.getTurnOrder()[0];

			if (currentSelectedUnit->unitInformation.allegiance != HUMAN_PLAYER)
			{
				startEnemyTurnTimer = true;
				enemyWaitTime.restart();
				startUnit = true;
				clearNodeArea(startArea);
			}
			else {
				tacticsArmyUI->initiativeSystem.getNextUnit();
				clearNodeArea(startArea);
				createMoveableArea(currentSelectedUnit);
			}
			
			UIInterface->updateModeString("Battle Mode");
		}
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
		switch (currentState)
		{
		case PREP:
			UIInterface->update();
			preGameStartUpPlacement(mousePos);
			break;
		case BATTLE:
			if (UIInterface->UIWaitPressed() && !hasAttacked)
				SkipTurn();
			else {
				if (currentHoverNodeID != -1 && battleGrid[currentHoverNodeID]->debugShape->getGlobalBounds().contains(mousePos) && !hasAttacked)
				{
					TakeUnitAction(battleGrid[currentHoverNodeID]);
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
		if (currentState == BATTLE && currentSelectedUnit && currentSelectedUnit->unitInformation.allegiance == HUMAN_PLAYER && !hasAttacked) {
			hoverMouseOnNode();
		}
		if (currentSelectedUnit && currentState ==PREP) {
			currentSelectedUnit = nullptr;
		}
	}
}

void BattleScene::TakeUnitAction(const std::shared_ptr<BattleGridNode>& _targetNode)
{
	auto findNodeByID = [](const auto& nodeIDs, int nodeID) {
		return std::ranges::find_if(nodeIDs, [nodeID](const auto& ID) {
			return ID == nodeID;
			});
		};

	auto processMovement = [&](int targetNodeID) {
		auto it = findNodeByID(walkableNodesIDs, targetNodeID);
		if (it != walkableNodesIDs.end() && _targetNode->getCurrentAllegiance() != currentSelectedUnit->unitInformation.allegiance) {
			aStarPathFind(battleGrid[currentSelectedUnit->getCurrentNodeId()], battleGrid[targetNodeID]);
			move = true;
			canAttack = false;
			Mouse::getInstance().SetToDefault();
		}
		};

	switch (currentSelectedUnit->unitInformation.unitType) {
	case RANGED:
		if (_targetNode->isOccupied() &&
			_targetNode->getCurrentAllegiance() != currentSelectedUnit->unitInformation.allegiance) {
			if (currentDefendingUnit) {
				clearArea(walkableNodesIDs);
				TriggerAttack();
				Mouse::getInstance().SetToDefault();
			}
		}
		else { // Handle movement
			processMovement(currentHoverNodeID);
		}
		break;

	case MELEE:
		if (_targetNode->isOccupied() &&
			_targetNode->getCurrentAllegiance() != currentSelectedUnit->unitInformation.allegiance) {
			if (currentDefendingUnit) {
				processMovement(attackNode); // Attack node
				hasAttacked = true;
			}
		}
		else if (!_targetNode->isOccupied()) { // Move to hover node
			processMovement(currentHoverNodeID);
		}
		break;
	}
}

void BattleScene::hoverMouseOnNode()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());

	// Track the node currently under the cursor
	int hoveredNodeID = -1;

	// Check which node is currently being hovered
	for (auto& node : battleGrid) {
		if (node->debugShape->getGlobalBounds().contains(mousePos)) {
			hoveredNodeID = node->getID();
			break; // Stop checking once the hovered node is found
		}
	}

	// Update the hovered node ID
	currentHoverNodeID = hoveredNodeID;

	// If no valid node is hovered, reset to default cursor
	if (currentHoverNodeID == -1) {
		Mouse::getInstance().SetToDefault();
		return;
	}

	// Handle logic for MELEE units
	if (currentSelectedUnit->unitInformation.unitType == MELEE) {
		Mouse::getInstance().SetToDefault();
		if (isNodeInRangeOfUnit()) {
			canAttack = true;
			auto node = battleGrid[currentHoverNodeID];
			pinpointMousePosition(mousePos, node);
		}
		else {
			canAttack = false;
			attackNode = -1;
			attackIcon.setPosition(sf::Vector2f(-200, -200)); // Offscreen
		}
	}

	// Handle logic for RANGED units
	else if (currentSelectedUnit->unitInformation.unitType == RANGED) {
		// Check if the hovered node contains an enemy
		attackIcon.setPosition(sf::Vector2f(-200, -200)); // Offscreen
		attackNode = -1;
		bool defaultIcon = true;
		for (auto& enemyUnit : enemyRef->getArmy()->getArmy()) {
			if (enemyUnit->getCurrentNodeId() == currentHoverNodeID && enemyUnit->unitStats.isActive) {
				Mouse::getInstance().SetToRanged();
				currentDefendingUnit = enemyUnit;
				defaultIcon = false;
				break;
			}
		}
		if(defaultIcon)
		{
			Mouse::getInstance().SetToDefault();
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
		auto it = std::ranges::find_if(walkableNodesIDs,
			[nodeID](const auto& ID) {
				return ID == nodeID;
			});

		if (it != walkableNodesIDs.end() && !battleGrid[nodeID]->isOccupied() || currentSelectedUnit->getCurrentNodeId() == nodeID) {
				attackNode = nodeID;
				attackIcon.setPosition(battleGrid[nodeID]->getMidPoint());
		}
		else
		//Puts icon on first neighbour of unit to attack if on edge of area
		{
			for (auto& node : battleGrid[currentHoverNodeID]->getNeighbours()) {
				auto iconPlace = std::find_if(walkableNodesIDs.begin(), walkableNodesIDs.end(), [node](int id) {
					return node.first->getID() == id;
					});
				if (iconPlace != walkableNodesIDs.end())
				{
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
			if (std::ranges::find(walkableNodesIDs.begin(), walkableNodesIDs.end(), node.first->getID()) != walkableNodesIDs.end()) {
				if (currentHoverNodeID == battleGrid[unit->getCurrentNodeId()]->getID() && unit->unitStats.isActive) {
					currentDefendingUnit = unit;
					return true;
				}
			}
		}
	}
	return false;
}

void BattleScene::moveUnit()
{
	if (path.empty()) {
		finalizeMoveUnit();
		return;
	}

	//distance to next node in path
	sf::Vector2f distance = path[currentNodeInPath]->getMidPoint() - currentSelectedUnit->getPosition();
	float magnitude = Utility::magnitude(distance.x, distance.y);

	if (magnitude < 2.0f) {
		currentNodeInPath++;

		if (currentNodeInPath == path.size()) {
			//final node reached
			finalizeMoveUnit();
			return;
		}

		//updated distance for next node
		distance = path[currentNodeInPath]->getMidPoint() - currentSelectedUnit->getPosition();
	}

	currentSelectedUnit->moveUnit(Utility::unitVector2D(distance));
}

void BattleScene::finalizeMoveUnit()
{
	//update new grid positions
	currentSelectedUnit->moveUnit(sf::Vector2f(0, 0));
	battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateOccupied(false);
	battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateAllegiance(NONE);
	if (currentNodeInPath != 0) {
		currentSelectedUnit->setCurrentNodeId(path[currentNodeInPath - 1]->getID());
	}
	battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateOccupied(true);
	battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateAllegiance(currentSelectedUnit->unitInformation.allegiance);

	if (scanForAttack) {
		searchNeighboursToAttack();
	}
	else if (attackNode != -1) {
		TriggerAttack();
		ParticleManager::getInstance().CreateBloodParticle(currentDefendingUnit->getPosition());
		calculateDamage(currentSelectedUnit, currentDefendingUnit); //damage calc
	}

	lastAttackedUnit = currentSelectedUnit;

	//reset
	move = false;
	currentNodeInPath = 0;
	currentDefendingUnit = nullptr;
	currentSelectedUnit = nullptr;
	attackNode = -1;

	//next turn
	startEnemyTurnTimer = true;
	scanForAttack = false;
	std::cout << "Before restart: " << enemyWaitTime.getElapsedTime().asSeconds() << std::endl;
	enemyWaitTime.restart();
	std::cout << "After restart: " << enemyWaitTime.getElapsedTime().asSeconds() << std::endl;

	if(!removeUnitAnimation)
		tacticsArmyUI->startAnimation();
	else
		tacticsArmyUI->startRemoveUnitAnimation(unitToRemove);
}

void BattleScene::searchNeighboursToAttack()
{
	auto nodeId = currentSelectedUnit->getCurrentNodeId();

	for (auto& neighbour : battleGrid[nodeId]->getNeighbours()) {
		if (currentDefendingUnit->getCurrentNodeId() == neighbour.first->getID() && currentDefendingUnit->unitStats.isActive) {
			TriggerAttack();
			ParticleManager::getInstance().CreateBloodParticle(currentDefendingUnit->getPosition());
			calculateDamage(currentSelectedUnit, currentDefendingUnit); //damage calc
			break;
		}
	}
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
					battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateAllegiance(NONE);
					currentSelectedUnit->placeUnit(node->getMidPoint());
					node->updateOccupied(true);
					currentSelectedUnit->setCurrentNodeId(node->getID());
					battleGrid[currentSelectedUnit->getCurrentNodeId()]->updateAllegiance(currentSelectedUnit->unitInformation.allegiance);
					break;
				}
			}
		}
	}
}

void BattleScene::clearArea(std::vector<int> _ids)
{
	for(auto& ID : _ids)
	{
		battleGrid[ID]->setTransparent();
	}
	_ids.clear();
}

void BattleScene::clearNodeArea(std::vector<std::shared_ptr<BattleGridNode>>& _vector)
{
	for (auto& node : _vector)
	{
		node->setTransparent();
	}
	_vector.clear();
}

void BattleScene::TriggerAttack()
{
	currentSelectedUnit->Attack(currentDefendingUnit->getPosition());
	hasAttacked = true;
	canAttack = false;

}


void BattleScene::SkipTurn()
{
	currentSelectedUnit = nullptr;
	attackNode = -1;
	move = false;
	canAttack = false;
	hasAttacked = false;
	currentNodeInPath = 0;
	clearArea(walkableNodesIDs);

	//next turn
	startEnemyTurnTimer = true;
	scanForAttack = false;
	enemyWaitTime.restart();

	tacticsArmyUI->startAnimation();
}

void BattleScene::EnemyTurn()
{
	//Ranged Unit Attack
	if (currentSelectedUnit->unitInformation.unitType == RANGED)
	{
		clearArea(walkableNodesIDs);

		currentDefendingUnit = PickUnitToAttack(playerRef->getArmy()->getArmy());

		TriggerAttack();
	}
	else
		//Melee Attack
	{
		int selectedNode = -1;
		auto closeEnemies = ScanNearByUnits();
		if (closeEnemies.empty()) //No nearby units
		{
			selectedNode = SelectNodeToWalkTo();
			//add ability to attack if you on edge node
			scanForAttack = true;
		}
		else
		{
			selectedNode = SelectAttackNodeToWalkTo(closeEnemies);
			attackNode = selectedNode;
		}
		aStarPathFind(battleGrid[currentSelectedUnit->getCurrentNodeId()], battleGrid[selectedNode]);
		move = true;
	}
	startEnemyTurnTimer = false;
}

void BattleScene::calculateDamage(const std::shared_ptr<PirateUnit>& _attacker, const std::shared_ptr<PirateUnit>& _defender)
{
	int damage = DamageCalculations::calculateHitPointsLost(_attacker, _defender);

	int lostUnitsAmount = _defender->TakeDamage(damage);
	floatingNumbers.push_back(std::make_unique<FloatingNumber>(_defender->getPosition(), lostUnitsAmount));

	assignDeadUnits(_defender, lostUnitsAmount);

	if (_defender->currentState == DEATH) { //dead
		removeUnitAnimation = true;
		unitToRemove = _defender;
		newAreaSet = false;
	}
}

void BattleScene::assignDeadUnits(const std::shared_ptr<PirateUnit>& _defender, int _amount)
{
	if (_amount > 0) {
		if (_defender->unitInformation.allegiance == enemyRef->GetEnemyTeam())
		{
			pickPerciseUnit(_defender, enemyArmyDead, _amount);
		}
		else
		{
			pickPerciseUnit(_defender, playerArmyDead, _amount);
		}
	}
}

void BattleScene::pickPerciseUnit(const std::shared_ptr<PirateUnit>& _defender, const std::unique_ptr<Army>& _ref, int _amount)
{
	switch (_defender->unitInformation.unitName)
	{
	case BUCCANEER:
		_ref->addUnit(std::make_shared<Buccaneer>(_amount, _defender->unitInformation.allegiance));
		break;
	case CANNON:
		_ref->addUnit(std::make_shared<CannonUnit>(_amount, _defender->unitInformation.allegiance));
		break;
	case GUNNER:
		_ref->addUnit(std::make_shared<Gunner>(_amount, _defender->unitInformation.allegiance));
		break;
	case BIRD:
		_ref->addUnit(std::make_shared<BirdUnit>(_amount, _defender->unitInformation.allegiance));
		break;
	case HARPOONER:
		_ref->addUnit(std::make_shared<Harpooner>(_amount, _defender->unitInformation.allegiance));
		break;
	}
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

std::shared_ptr<PirateUnit> BattleScene::PickUnitToAttack(const std::vector<std::shared_ptr<PirateUnit>>& _possibleUnits) const 
{
	int highestDamage = 0;

	std::shared_ptr<PirateUnit> selectedUnit;
	for(auto & unit : _possibleUnits)
	{
		if (unit->unitStats.isActive) {
			int predictedDamage = DamageCalculations::calculateHitPointsLost(currentSelectedUnit, unit);
			if (predictedDamage > highestDamage) //Damage will always prioritise the closest units
			{
				selectedUnit = unit;
				highestDamage = DamageCalculations::calculateHitPointsLost(currentSelectedUnit, unit);
			}
			//Unit will die so prioritise
			if(!DamageCalculations::calculateDamage(unit->unitStats, unit->unitBaseStats, predictedDamage).isActive)
			{
				return unit;
			}
		}
	}
	return selectedUnit;
}

int BattleScene::SelectNodeToWalkTo()
{
	int shortestDistance = 1000;
	int selectedID = -1;

	std::shared_ptr<PirateUnit> selectedUnit = PickUnitToAttack(playerRef->getArmy()->getArmy());
	for (auto& ID : walkableNodesIDs)
	{
		if (selectedUnit){
		if (EnemyMoveConditions::distanceToEnemy(battleGrid[ID]->getMidPoint(), selectedUnit->getPosition()) < shortestDistance)
		{
			shortestDistance = EnemyMoveConditions::distanceToEnemy(battleGrid[ID]->getMidPoint(), selectedUnit->getPosition());
			currentDefendingUnit = selectedUnit;
			selectedID = ID;
			canAttack = false;
		}
		}
	}
	return selectedID;
}

int BattleScene::SelectAttackNodeToWalkTo(const std::vector<std::shared_ptr<PirateUnit>>& _possibleUnits) 
{
	int shortestDistance = 1000;
	int selectedID = -1;

	currentDefendingUnit = PickUnitToAttack(_possibleUnits);
	auto enemyNode = battleGrid[currentDefendingUnit->getCurrentNodeId()];

	auto possibleAttackNodes = PathFindingFunctions<BattleGridNode>::BreathSearchNodes(battleGrid, enemyNode, 1); //nodes neighbouring enemy position

	for (auto& ID : possibleAttackNodes)
	{
		if (EnemyMoveConditions::distanceToEnemy(battleGrid[ID]->getMidPoint(), currentSelectedUnit->getPosition()) < shortestDistance)
		{
			shortestDistance = EnemyMoveConditions::distanceToEnemy(battleGrid[ID]->getMidPoint(), currentSelectedUnit->getPosition());
			selectedID = ID;
		}
	}

	return selectedID;
}

bool BattleScene::CheckBattleOver(const std::unique_ptr<Army>& _army)
{
	if (_army->isEmpty())
	{
		endBattleUI->updateUnitsDestroyed(enemyArmyDead);
		endBattleUI->updateUnitsLost(playerArmyDead);
		
		if (_army->getArmy()[0]->unitInformation.allegiance == HUMAN_PLAYER)
		{
			UIInterface->updateModeString("Enemy Wins");
			RemoveDeadUnits();
			endBattleUI->Lose();
		}
		else
		{
			UIInterface->updateModeString("Player Wins");
			RemoveDeadUnits();
			endBattleUI->Win();
			AddCoinsToPlayer();
			
		}
		currentState = END;
		endGameTimer.restart();
		return true;
	}
	return false;
}

void BattleScene::AddCoinsToPlayer()
{
	int totalGoldWin = 2000;
	if (playerRef->getHiredEnemy())
		totalGoldWin = 1000;
	else
		totalGoldWin = 2000;

	playerRef->getInventory()->addItem(std::make_unique<Coins>(totalGoldWin));
}

void BattleScene::RemoveDeadUnits()
{
	for (int i = 0; i < playerArmyDead->getArmy().size(); i++)
	{
		if (!playerArmyDead->getArmy()[i]->unitStats.isActive)
		{
			playerArmyDead->deleteUnit(playerArmyDead->getArmy()[i]);
		}
	}
	for (int i = 0; i < playerRef->getArmy()->getArmy().size(); i++)
	{
		if (!playerRef->getArmy()->getArmy()[i]->unitStats.isActive)
		{
			playerRef->getArmy()->deleteUnit(playerRef->getArmy()->getArmy()[i]);
		}
	}
	for (int i = 0; i < enemyArmyDead->getArmy().size(); i++)
	{
		if (!enemyArmyDead->getArmy()[i]->unitStats.isActive)
		{
			enemyArmyDead->deleteUnit(enemyArmyDead->getArmy()[i]);
		}
	}
}

void BattleScene::WaitForTurn()
{
	if(enemyWaitTime.getElapsedTime().asSeconds() > turnWaitTime)
	{
		if (removeUnitAnimation) {
			if (tacticsArmyUI->finsihedAnimation) {
				removeUnitAnimation = false;
				enemyWaitTime.restart();
				tacticsArmyUI->finsihedAnimation = false;
				tacticsArmyUI->animateRemoveUnit = false;
				tacticsArmyUI->initiativeSystem.removeUnit(unitToRemove);
				tacticsArmyUI->UpdateToInitiativeViewAfterUnitRemoved(lastAttackedUnit);
				unitToRemove = nullptr;
				tacticsArmyUI->startAnimation();
				turnWaitTime = 1.f;
			}
		}
		else if (updateNextTurn()) {
			turnWaitTime = 1.f;
			startEnemyTurnTimer = false;
			hasAttacked = false;
		}
	}
}

void BattleScene::WaitForEndGameTimer()
{
	if (endGameTimer.getElapsedTime().asSeconds() > 0.75f)
	{
		showEndGame = true;
	}
}

std::vector <std::shared_ptr<PirateUnit>> BattleScene::ScanNearByUnits()
{
	std::vector<std::shared_ptr<PirateUnit>> possibleUnits;

	for (auto& unit : playerRef->getArmy()->getArmy()) {
		if (unit->unitStats.isActive) {
			if (EnemyMoveConditions::distanceToEnemy(currentSelectedUnit->getPosition(), unit->getPosition()) <= currentSelectedUnit->unitStats.speed) //unit close
			{
				possibleUnits.push_back(unit);
			}
		}
	}

	return possibleUnits;
}

