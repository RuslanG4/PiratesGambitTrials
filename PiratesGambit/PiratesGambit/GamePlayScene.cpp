#include "GamePlayScene.h"

GamePlayScene::GamePlayScene()
{
	myPlayer = std::make_shared<Player>(sf::Vector2f(25, 25));
	playerBoat = std::make_shared<Boat>(sf::Vector2f(25, 25), myPlayer);
	//myPlayer->boardBoat(playerBoat);

	playerMenu = std::make_unique<PlayerTabMenu>(myPlayer->getArmy(), myPlayer->getInventory());
	RenderableInventory::getInstance().Init();
	HireRecruitUI::getInstance().PassPlayer(myPlayer);

	myMap = std::make_unique<FullMap>(mapSize, myPlayer);

	SpawnPlayer();
	UpdatePlayerCurrentNode(); // sets player current Node

	SpawnEnemies();

	UpdateEnemiesCurrentNode();

	battleScene = std::make_unique<BattleScene>(myPlayer);
}

void GamePlayScene::handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent)
{
	Camera::getInstance().handleZooming(newEvent);
	if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
	{
		if (myPlayer->isOnBoat()) {
			playerBoat->processKeys(newEvent);
		}
	}
	if (sf::Event::KeyReleased == newEvent.type)
	{
		processKeyUp(newEvent);
		if (myPlayer->isOnBoat()) {
			playerBoat->processKeyUp(newEvent);
		}
	}
	if (sf::Event::MouseButtonPressed == newEvent.type) //user pressed mouse
	{
		Mouse::getInstance().processMouse(newEvent);
		if (!battle && currentObjectInteract.lock()) {
			transferInventoryItems();
		}
	}
	if (battleScene) {
		battleScene->handleEvent(newEvent);
	}

}

void GamePlayScene::update(float dt)
{
	Camera::getInstance().update(myPlayer->getPlayerController()->getPosition(), sf::Vector2f(mapSize * CHUNK_NODE_COLS * NODE_SIZE, mapSize * CHUNK_NODE_COLS * NODE_SIZE));
	//Camera::getInstance().setCameraCenter(myPlayer->getPlayerController()->getPosition());

	if (!battle && !battleTransition.IsTransitionActive()) {
		updateVisableNodes();
		HandleMovement();
		processKeys();
		UpdatePlayerCurrentNode();
		UpdateEnemiesCurrentNode();

		for (int index : visibleNodes) {
			std::shared_ptr<Node> node = myMap->getFullMap()[index];

			if (node->GetBuilding())
				node->GetBuilding()->Update(dt);
			if (node->GetObject())
				node->GetObject()->update(dt);
		}

		for (auto& updateableNode : myPlayer->getUpdateableArea()->getUpdateableNodes())
		{
			interactWithObjects(updateableNode);
			transitionToBattleMode(updateableNode);
		}
		handleKeyPopUps();

		if (myPlayer->isOnBoat())
		{
			playerBoat->update(dt);
		}
		else
		{
			myPlayer->update(dt);
		}

		playerMenu->Update();

		UpdateEnemies(dt);
		HandleProjectiles();

	}
	else if (battleTransition.IsTransitionActive())
	{
		battleTransition.Update();
		if (battleTransition.IsTransitionActive() == false)
		{
			battle = true;
		}
	}
	else {
		battleScene->update(dt);
		if (battleScene->isBattleOver()) {
			battle = false;
			auto enemyRef = battleScene->getEnemyRef();
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemyRef), enemies.end());
			battleScene->setEnemyRef(nullptr);
		}
	}
	if (AllianceDialogueUI::getInstance().isMenuOpen())
	{
		AllianceDialogueUI::getInstance().Update();
	}
	HireRecruitUI::getInstance().Update(dt);
	KeyPopUpManager::getInstance().Update(dt);
}

void GamePlayScene::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	if (!battle) {
		window->setView(Camera::getInstance().getCamera());
		HandleEnemyScoutUI(window);

		for (int index : visibleNodes) {
			std::shared_ptr<Node> node = myMap->getFullMap()[index];

			window->draw(*(node->waterBackSprite));
			window->draw(*(node->drawableNode));

		}

		myPlayer->render(window);

		playerBoat->render(window);

		for (auto& boat : enemyBoats)
		{
			boat->render(window);
		}
		for (auto& enemy : enemies)
		{
			enemy->render(window);
		}

		for (int index : visibleNodes) {
			std::shared_ptr<Node> node = myMap->getFullMap()[index];

			if (node->GetObject()) {
				node->GetObject()->render(window);
			}

			if (node->GetBuilding()) {
				node->GetBuilding()->Render(window);
			}
		}

		
		playerMenu->Render(window);
	}
	else
	{
		battleScene->render(window);
	}
	BulletFactory::getInstance().render(window);
	ParticleManager::getInstance().render(window);

	

	UnitStatsDisplay::getInstance().Render(window);
	EnemyScoutUI::getInstance().Render(window);

	window->setView(Camera::getInstance().getCamera());

	battleTransition.Render(window);

	if (AllianceDialogueUI::getInstance().isMenuOpen())
	{
		AllianceDialogueUI::getInstance().Render(window);
	}
	if (RenderableInventory::getInstance().isOpen())
	{
		RenderableInventory::getInstance().render(window);
	}
	if (HireRecruitUI::getInstance().IsMenuOpen())
	{
		HireRecruitUI::getInstance().Render(window);
	}

	if (!HireRecruitUI::getInstance().IsUIOpen() && !AllianceDialogueUI::getInstance().isMenuOpen() && !RenderableInventory::getInstance().isOpen() && !PlayerTabMenu::isMenuOpen() && !battle)
	{
		KeyPopUpManager::getInstance().Render(window);
	}
	
}

void GamePlayScene::SpawnPlayer()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> chunkDist(0, myMap->getChunks().size() - 1);

	int randomChunkIndex = chunkDist(gen);
	auto chunk = myMap->getChunks()[randomChunkIndex].get();

	while (chunk->getIslands().empty())
	{
		randomChunkIndex = chunkDist(gen);
		chunk = myMap->getChunks()[randomChunkIndex].get();
	}

	auto islands = chunk->getIslands()[0];

	std::uniform_int_distribution<int> nodeDist(0, islands->getLandNodes().size() - 1);
	int nodeIndex = nodeDist(gen);

	while (islands->getLandNodes()[nodeIndex]->isOccupied())
	{
		nodeIndex = nodeDist(gen);
	}

	myPlayer->updatePosition(islands->getLandNodes()[nodeIndex]->getMidPoint());

	SpawnBoat(islands);

}

void GamePlayScene::SpawnBoat(const std::shared_ptr<Island>& _island)
{
	for (auto& sandNode : _island->getSandNodes())
	{
		for (auto& neighbor : sandNode->getNeighbours())
		{
			if (!neighbor.first->getIsLand() && !neighbor.first->isOccupied())
			{
				playerBoat->setPosition(neighbor.first->getMidPoint());
				playerBoat->setDockedNode(neighbor.first);
				return;
			}
		}
	}
}

void GamePlayScene::SpawnEnemies()
{
	auto& chunks = myMap->getChunks();
	std::vector<int> availableChunkIndices;

	if (availableChunkIndices.empty())
	{
		availableChunkIndices.resize(chunks.size());
		std::iota(availableChunkIndices.begin(), availableChunkIndices.end(), 0);
	}

	std::mt19937 gen(rd());

	auto SelectAndSpawn = [&](const UnitAllegiance& _enemyAllegiance) {
		if (availableChunkIndices.empty()) return;

		std::uniform_int_distribution<int> chunkDist(0, availableChunkIndices.size() - 1);
		int selectedIndex = chunkDist(gen);
		int chunkIndex = availableChunkIndices[selectedIndex];

		SpawnTeam(chunkIndex, _enemyAllegiance);
		availableChunkIndices.erase(availableChunkIndices.begin() + selectedIndex);
		};

	std::vector<UnitAllegiance> enemyAllegiances = { BLUE_PLAYER, BLACK_PLAYER, RED_PLAYER };

	for (const auto& allegiance : enemyAllegiances)
	{
		SelectAndSpawn(allegiance);
	}
}

void GamePlayScene::InitialiseEnemyArmy(const std::shared_ptr<Enemy>& _enemyRef, nlohmann::json& jsonData)
{
	for (const auto& allegianceData : jsonData) {
		if (allegianceData["Allegiance"] == _enemyRef->GetEnemyAllegiance()) {
			// Search for the correct EnemyId within the allegiance
			for (const auto& enemyData : allegianceData["Enemies"]) {
				if (enemyData["EnemyId"] == _enemyRef->GetEnemyID()) {
					_enemyRef->setPirateName(enemyData["name"]);
					_enemyRef->setAllegiance(allegianceData["PlayerReputation"]);
					for (const auto& unitData : enemyData["army"]) {

						if (unitData["unittype"] == "Buccaneer") {
							_enemyRef->getArmy()->addUnitNoCombine(std::make_shared<Buccaneer>(unitData["amount"], _enemyRef->GetEnemyTeam()));
						}
						else if (unitData["unittype"] == "Gunner") {
							_enemyRef->getArmy()->addUnitNoCombine(std::make_shared<Gunner>(unitData["amount"], _enemyRef->GetEnemyTeam()));
						}
						else if (unitData["unittype"] == "Harpooner") {
							_enemyRef->getArmy()->addUnitNoCombine(std::make_shared<Harpooner>(unitData["amount"], _enemyRef->GetEnemyTeam()));
						}
						else if (unitData["unittype"] == "Cannon") {
							_enemyRef->getArmy()->addUnitNoCombine(std::make_shared<CannonUnit>(unitData["amount"], _enemyRef->GetEnemyTeam()));
						}
						else if (unitData["unittype"] == "Bird") {
							_enemyRef->getArmy()->addUnitNoCombine(std::make_shared<BirdUnit>(unitData["amount"], _enemyRef->GetEnemyTeam()));
						}
						else {
							std::cerr << "Unknown unit type: " << unitData["unittype"] << "\n";
						}
					}
				}
			}
		}
	}
}

void GamePlayScene::SpawnTeam(int _chunkIndex, const UnitAllegiance& _allegiance)
{
	std::mt19937 gen(rd());

	auto nodes = myMap->getChunks()[_chunkIndex]->nodeGrid;

	std::uniform_int_distribution<int> randomWater(0, nodes.size() - 1);

	std::ifstream file("ASSETS\\FILES\\EnemyStartingArmies.json");
	if (!file.is_open()) {
		std::cerr << "Failed to open file\n";
		return;
	}

	nlohmann::json jsonData;
	file >> jsonData;
	file.close();

	int currentTeamSize = FindCurrentTeamSize(jsonData, _allegiance);

	for (int i = 0; i < currentTeamSize; i++) {

		int waterNode = randomWater(gen);

		while (myMap->getChunks()[_chunkIndex]->nodeGrid[waterNode]->getIsLand())
		{
			waterNode = randomWater(gen);
		}

		if (waterNode)
		{
			auto enemy = std::make_shared<Enemy>(myPlayer, i ,_allegiance);
			InitialiseEnemyArmy(enemy, jsonData);
			auto enemyBoat = std::make_shared<EnemyBoat>(enemy, _allegiance);

			enemyBoat->setPosition(myMap->getChunks()[_chunkIndex]->nodeGrid[waterNode]->getMidPoint());
			enemyBoat->setDockedNode(myMap->getChunks()[_chunkIndex]->nodeGrid[waterNode]);
			enemy->boardBoat(enemyBoat);

			enemies.push_back(enemy);
			enemyBoats.push_back(enemyBoat);
		}
	}
}

void GamePlayScene::processKeyUp(sf::Event& t_event)
{
	if (t_event.key.code == sf::Keyboard::V)
	{
		keyUp = true;
	}
	if (t_event.key.code == sf::Keyboard::E)
	{
		interactWithObject = false;
	}
	if (t_event.key.code == sf::Keyboard::Tab)
	{
		interactWithObject = false;
	}
}

void GamePlayScene::processKeys()
{
	if (!Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && keyUp)
		{
			keyUp = false;
			if (!myPlayer->isOnBoat()) {
				for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
				{
					if (node == playerBoat->getDockedNode())
					{
						myPlayer->boardBoat(playerBoat);
						break;
					}
				}
			}
			else
			{
				for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
				{
					if (node->getIsLand())
					{
						myPlayer->disembarkBoat(node);
						playerBoat->setDockedNode(myPlayer->getCurrentNode());
						break;
					}
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !AllianceDialogueUI::getInstance().isMenuOpen())
	{
		for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
		{
			for (auto& enemy : enemies)
			{
				if (enemy->getCurrentNode() == node && !enemy->GetPlayerAllegiance().isHostile())
				{
					AllianceDialogueUI::getInstance().OpenMenu(enemy);
					enemy->ChangeState(new IdleState(myPlayer));
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !interactWithObject && !Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen() && !PlayerTabMenu::isMenuOpen())
	{
		interactWithObject = true;
		playerMenu->Interact(myPlayer);
	}

}

void GamePlayScene::HandleEnemyScoutUI(const std::unique_ptr<sf::RenderWindow>& window)
{
	for (auto& enemy : enemies)
	{
		sf::Vector2f mousePos = window->mapPixelToCoords(Mouse::getInstance().getMousePosition());
		float menuWidth = EnemyScoutUI::getInstance().getWidth();
		float menuHeight = EnemyScoutUI::getInstance().getHeight();

		if (Mouse::getInstance().RightClicked() && enemy->GetGlobalBounds().contains(mousePos))
		{
			EnemyScoutUI::getInstance().passArmy(enemy->getArmy(), enemy->GetPirateName());

			sf::Vector2f enemyPos = enemy->GetPosition(); 

			if (enemyPos.x > myPlayer->getPlayerController()->getPosition().x)
			{
				enemyPos.x -= menuWidth;
			}

			if (enemyPos.y > myPlayer->getPlayerController()->getPosition().y)
			{
				enemyPos.y -= menuHeight;
			}

			EnemyScoutUI::getInstance().placeMenu(enemyPos);
			EnemyScoutUI::getInstance().OpenMenu();
		}
		if (EnemyScoutUI::getInstance().isDisplayOpen() && !Mouse::getInstance().RightClicked())
		{
			EnemyScoutUI::getInstance().CloseMenu();
		}
	}
}

void GamePlayScene::HandleMovement() const
{
	if (!Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen()) {
		sf::Vector2f desiredVelocity{ 0,0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (myPlayer->isOnBoat())
			{
				playerBoat->getController()->increaseSpeed();
			}
			else
			{
				desiredVelocity.y--;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (myPlayer->isOnBoat())
			{
				playerBoat->getController()->decreaseSpeed();
			}
			else
			{
				desiredVelocity.y++;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (myPlayer->isOnBoat())
			{
				playerBoat->getController()->decreaseRotation();
			}
			else
			{
				desiredVelocity.x--;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (myPlayer->isOnBoat())
			{
				playerBoat->getController()->increaseRotation();
			}
			else
			{
				desiredVelocity.x++;
			}
		}
		myPlayer->getPlayerController()->setLandVelocity(desiredVelocity);
	}
}

void GamePlayScene::HandleProjectiles()
{
	bool found = false;
	auto& projectiles = BulletFactory::getInstance().GetProjectiles();

	for (auto it = projectiles.begin(); it != projectiles.end(); )
	{
		for (auto& boat : enemyBoats) {
			if ((*it)->getBounds().intersects(boat->GetGlobalBounds()))
			{
				boat->takeDamage();
				ParticleManager::getInstance().CreateExplosionParticle(boat->getPosition());
				if (boat->isAlive()) {
					if (!boat->getEnemyRef()->isOnBoat()) {
						boat->getEnemyRef()->ChangeState(new FindBoatState(myPlayer));
					}
					else {
						boat->getEnemyRef()->LoseArmy();
					}
					boat->getEnemyRef()->updateAllegiance(-40); // - 40 rep
				}
				else {
					boat->getEnemyRef()->markForDeath();
					RemoveEnemy();
				}
				it = projectiles.erase(it);
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
		else {
			it++;
		}
	}
}

void GamePlayScene::RemoveEnemy() 
{
	enemyBoats.erase(
		std::remove_if(enemyBoats.begin(), enemyBoats.end(),
			[](const std::shared_ptr<EnemyBoat>& boat) {
				return !boat->isAlive();
			}),
		enemyBoats.end());
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
			[](const std::shared_ptr<Enemy>& enemy) {
				return !enemy->isAlive();
			}),
		enemies.end());
}

std::shared_ptr<Node> GamePlayScene::FindCurrentNode(sf::Vector2f _position) const
{
	int chunkSizeInNodes = NODE_SIZE;
	int nodeSize = NODE_SIZE;

	int chunkX = static_cast<int>(_position.x) / (chunkSizeInNodes * nodeSize);
	int chunkY = static_cast<int>(_position.y) / (chunkSizeInNodes * nodeSize);
	int chunkID = chunkX * mapSize + chunkY;  // Column-major ordering

	// Ensure the chunkID is valid
	if (chunkID < 0 || chunkID >= 25) return nullptr;

	int localX = (static_cast<int>(_position.x) % (chunkSizeInNodes * nodeSize)) / nodeSize;
	int localY = (static_cast<int>(_position.y) % (chunkSizeInNodes * nodeSize)) / nodeSize;
	int nodeIndex = localY * chunkSizeInNodes + localX;

	auto& nodeGrid = myMap->getChunks()[chunkID]->nodeGrid;
	if (nodeIndex >= 0 && nodeIndex < nodeGrid.size()) {
		return nodeGrid[nodeIndex];
	}

	return nullptr;
}

void GamePlayScene::UpdatePlayerCurrentNode() const
{
	auto playerCurrentNode = FindCurrentNode(myPlayer->getPlayerController()->getPosition());
	if (myPlayer->getCurrentNode() != playerCurrentNode) {
		myPlayer->setCurrentNode(playerCurrentNode);
		myPlayer->updateUpdateableArea(playerCurrentNode, 1);
		std::cout << "Current Node : " << playerCurrentNode->getID() << "\n";
	}
}

void GamePlayScene::UpdateEnemiesCurrentNode() const
{
	for (auto& enemy : enemies)
	{
		auto enemyCurrentNode = FindCurrentNode(enemy->GetPosition());
		if (enemy->getCurrentNode() != enemyCurrentNode) {
			enemy->setCurrentNode(enemyCurrentNode);
			enemy->updateUpdateableArea(enemyCurrentNode, 6);
		}
	}
}

void GamePlayScene::transitionToBattleMode(const std::shared_ptr<Node>& _node)
{
	for (auto& enemy : enemies)
	{
		if (_node->getID() == enemy->getCurrentNode()->getID())
		{
			if (enemy->GetGlobalBounds().intersects(myPlayer->GetHitBox()))
			{
				battleTransition.startTransition(1);
				battleScene->setEnemyRef(enemy);
				battleScene->resetBattle();
			}
		}
	}
}

void GamePlayScene::interactWithObjects(const std::shared_ptr<Node>& _node)
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::E)) && !interactWithObject && !Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen() && !PlayerTabMenu::isMenuOpen())
	{
		if (_node->GetObject()) {

			if (_node->GetObject()->getID() == _node->getID())
			{
				_node->GetObject()->interact();
				myPlayer->getPlayerController()->setLandVelocity(sf::Vector2f(0, 0));
				currentObjectInteract = _node->GetObject();
				interactWithObject = true;
			}
		}
		else if (_node->GetBuilding())
		{
			if (interactWithBuildings(_node)) {
				myPlayer->getPlayerController()->setLandVelocity(sf::Vector2f(0, 0));
			}
		}
	}

}

bool GamePlayScene::interactWithBuildings(const std::shared_ptr<Node>& _node)
{
	for (auto& nodeId : _node->GetBuilding()->GetOccupiedNodeIds())
	{
		if (nodeId == _node->getID())
		{
			_node->GetBuilding()->Interact();
			return true;
		}
	}

	return false;
}

void GamePlayScene::handleKeyPopUps()
{
	auto& updateableNodes = myPlayer->getUpdateableArea()->getUpdateableNodes();
	auto playerPos = myPlayer->getPlayerController()->getPosition();

	bool showXKey = std::any_of(enemies.begin(), enemies.end(),
		[&](const std::shared_ptr<Enemy>& enemy) {
			return !enemy->GetPlayerAllegiance().isHostile() &&
				std::find(updateableNodes.begin(), updateableNodes.end(), enemy->getCurrentNode()) != updateableNodes.end();
		});

	if (showXKey) {
		KeyPopUpManager::getInstance().showKey(playerPos, "X-KEY");
		return;
	}

	auto playerBoatPtr = playerBoat;

	if (myPlayer->isOnBoat()) {
		bool landNearby = std::any_of(updateableNodes.begin(), updateableNodes.end(),
			[](const std::shared_ptr<Node>& node) {
				return node->getIsLand();
			});

		if (landNearby) {
			KeyPopUpManager::getInstance().showKey(playerPos, "V-KEY");
		}
		else {
			KeyPopUpManager::getInstance().hideKey();
		}
	}
	else {
		bool nearBoatDock = std::find(updateableNodes.begin(), updateableNodes.end(), playerBoatPtr->getDockedNode()) != updateableNodes.end();
		bool nearBuilding = std::any_of(updateableNodes.begin(), updateableNodes.end(),
			[](const std::shared_ptr<Node>& node) {
				return node->GetBuilding();
			});
		bool nearObject = std::any_of(updateableNodes.begin(), updateableNodes.end(),
			[](const std::shared_ptr<Node>& node) {
				return node->GetObject() && node->GetObject()->getName() == BARREL;
			});

		if (nearBoatDock) {
			KeyPopUpManager::getInstance().showKey(playerPos, "V-KEY");
		}
		else if (nearBuilding || nearObject) {
			KeyPopUpManager::getInstance().showKey(playerPos, "E-KEY");
		}
		else {
			KeyPopUpManager::getInstance().hideKey();
		}
	}
}


void GamePlayScene::transferInventoryItems()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	for (auto& slot : RenderableInventory::getInstance().getSlots())
	{
		if (Mouse::getInstance().LeftClicked() && slot->getIsOccupied())
		{
			if (slot->getBackgroundSprite().getGlobalBounds().contains(mousePos))
			{
				std::unique_ptr<InventoryItem> item = currentObjectInteract.lock()->getInventory()->removeItem(slot->getOccupiedBy());
				slot->clearSlot();
				myPlayer->getInventory()->addItem(std::move(item));
			}
		}
	}
}

void GamePlayScene::updateVisableNodes()
{
	sf::FloatRect viewBounds(Camera::getInstance().getCamera().getCenter() - (Camera::getInstance().getCamera().getSize() + sf::Vector2f(128, 128)) / 2.0f, Camera::getInstance().getCamera().getSize() + sf::Vector2f(128, 128));

	int minX = std::max(0, static_cast<int>(viewBounds.left / NODE_SIZE));
	int maxX = std::min(NODE_SIZE * mapSize - 1, static_cast<int>((viewBounds.left + viewBounds.width) / NODE_SIZE));
	int minY = std::max(0, static_cast<int>(viewBounds.top / NODE_SIZE));
	int maxY = std::min(NODE_SIZE * mapSize - 1, static_cast<int>((viewBounds.top + viewBounds.height) / NODE_SIZE));

	std::set<int> newVisibleNodes;

	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			int index = y * (NODE_SIZE * mapSize) + x;
			newVisibleNodes.insert(index);
		}
	}

	visibleNodes = std::move(newVisibleNodes);
}

void GamePlayScene::UpdateEnemies(double _dt)
{
	for(auto& enemy : enemies)
	{
		enemy->update(_dt);
	}
	for (auto& boat : enemyBoats)
	{
		boat->update(_dt);
	}
}

int GamePlayScene::FindCurrentTeamSize(nlohmann::json& jsonData, const UnitAllegiance& _allegiance)
{
	std::string allegianceStr;

	switch (_allegiance)
	{
	case YELLOW_PLAYER:
		allegianceStr = "Yellow";
		break;
	case RED_PLAYER:
		allegianceStr = "Red";
		break;
	case BLUE_PLAYER:
		allegianceStr = "Blue";
		break;
	case GREEN_PLAYER:
		allegianceStr = "Green";
		break;
	case BLACK_PLAYER:
		allegianceStr = "Black";
		break;
	}

	for (const auto& allegianceData : jsonData) {
		if (allegianceData["Allegiance"] == allegianceStr) {
			return allegianceData["Enemies"].size();
		}
	}

	return 0;
}
