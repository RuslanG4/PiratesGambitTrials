#include "GamePlayScene.h"

GamePlayScene::GamePlayScene()
{
	myPlayer = std::make_shared<Player>(sf::Vector2f(25, 25));
	playerBoat = std::make_shared<Boat>(sf::Vector2f(25, 25), myPlayer);
	myPlayer->boardBoat(playerBoat);

	playerMenu = std::make_unique<PlayerTabMenu>(myPlayer->getArmy(), myPlayer->getInventory());
	RenderableInventory::getInstance().Init();
	HireRecruitUI::getInstance().PassPlayer(myPlayer);

	myMap = std::make_unique<FullMap>(mapSize, myPlayer);

	UpdatePlayerCurrentNode(); // sets player current Node

	for (int i = 0; i < 1; i++)
	{
		auto enemy = std::make_shared<Enemy>(myPlayer);
		auto enemyBoat = std::make_shared<EnemyBoat>(sf::Vector2f(325 + i * 100, 25), enemy, TextureManager::getInstance().getTexture("RED_BOAT"));
		enemy->boardBoat(enemyBoat);
		enemies.push_back(enemy);
		enemyBoats.push_back(enemyBoat);
	}

	UpdateEnemiesCurrentNode();

	//playerBoat->addCannonBall();

	battleScene = std::make_unique<BattleScene>(myPlayer, enemies[0]);
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

}

void GamePlayScene::update(float dt)
{
	Camera::getInstance().setCameraCenter(myPlayer->getPlayerController()->getPosition());

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

			for (auto& updateableNode : myPlayer->getUpdateableArea()->getUpdateableNodes())
			{
				if (node == updateableNode)
				{
					interactWithObjects(node);
					transitionToBattleMode(node);
				}
			}

		}

		if (myPlayer->isOnBoat())
		{
			playerBoat->update(dt);
		}
		else
		{
			myPlayer->update(dt);
		}

		playerMenu->Update();

		for (auto& enemy : enemies)
		{
			enemy->update(dt);
		}

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
	}
	if (AllianceDialogueUI::getInstance().isMenuOpen())
	{
		AllianceDialogueUI::getInstance().Update();
	}
	HireRecruitUI::getInstance().Update(dt);
}

void GamePlayScene::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	if (!battle) {
		window->setView(Camera::getInstance().getCamera());

		for (int index : visibleNodes) {
			std::shared_ptr<Node> node = myMap->getFullMap()[index];

			window->draw(*(node->waterBackSprite));
			window->draw(*(node->drawableNode));

		}

		myPlayer->render(window);

		playerBoat->render(window);

		for (auto& enemy : enemies)
		{
			enemy->render(window);
		}
		for (auto& boat : enemyBoats)
		{
			boat->render(window);
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

	UnitStatsDisplay::getInstance().Render(window);

	window->setView(Camera::getInstance().getCamera());

	battleTransition.Render(window);

	if (AllianceDialogueUI::getInstance().isMenuOpen())
	{
		AllianceDialogueUI::getInstance().Render(window);
	}
	if(RenderableInventory::getInstance().isOpen())
	{
		RenderableInventory::getInstance().render(window);
	}
	if(HireRecruitUI::getInstance().IsMenuOpen())
	{
		HireRecruitUI::getInstance().Render(window);
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
				std::cout << "R clicked" << "\n";
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
				if (enemy->getCurrentNode() == node && !enemy->GetPlayerAllegiance()->isHostile())
				{
					AllianceDialogueUI::getInstance().OpenMenu();
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

std::shared_ptr<Node> GamePlayScene::FindCurrentNode(sf::Vector2f _position) const
{
	int chunkSizeInNodes = 32;
	int nodeSize = 32;

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
			enemy->updateUpdateableArea(enemyCurrentNode, 4);
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

	int minX = std::max(0, static_cast<int>(viewBounds.left / 32));
	int maxX = std::min(32 * mapSize - 1, static_cast<int>((viewBounds.left + viewBounds.width) / 32));
	int minY = std::max(0, static_cast<int>(viewBounds.top / 32));
	int maxY = std::min(32 * mapSize - 1, static_cast<int>((viewBounds.top + viewBounds.height) / 32));

	std::set<int> newVisibleNodes;

	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			int index = y * (32 * mapSize) + x;
			newVisibleNodes.insert(index);
		}
	}

	visibleNodes = std::move(newVisibleNodes);
}
