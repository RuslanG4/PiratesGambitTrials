#include "GamePlayScene.h"

GamePlayScene::GamePlayScene()
{
	myPlayer = std::make_shared<Player>(sf::Vector2f(25, 25));

	playerMenu = std::make_unique<PlayerTabMenu>(myPlayer->getArmy(), myPlayer->getInventory());

	myMap = std::make_unique<FullMap>(mapSize, myPlayer); //keep 1x1, 2x2

	/*auto enemy = std::make_shared<Enemy>(myPlayer);
	auto enemy2 = std::make_shared<Enemy>(myPlayer);*/

	for(int i =0;i<4;i++)
	{
		auto enemy = std::make_shared<Enemy>(myPlayer);

		FindCurrentChunk();
		FindCurrentNode();

		auto enemyBoat = std::make_shared<EnemyBoat>(sf::Vector2f(325 + i * 100, 25), enemy, TextureManager::getInstance().getTexture("RED_BOAT"));

		enemy->boardBoat(enemyBoat);
		enemies.push_back(enemy);
		enemyBoats.push_back(enemyBoat);
	}

	playerBoat = std::make_shared<Boat>(sf::Vector2f(25, 25), myPlayer);

	FindCurrentChunk();
	FindCurrentNode();

	//enemy->boardBoat(enemyBoat);

	myPlayer->boardBoat(playerBoat);

	playerBoat->addCannonBall();

	battleScene = std::make_unique<BattleScene>(myPlayer, enemies[0]);

	/*myMap->getChunks()[0]->getIslands()[0]->PlaceEnemy(enemy);*/

}

void GamePlayScene::handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent)
{

	if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
	{
		processKeys(newEvent);
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
		FindCurrentChunk();
		FindCurrentNode();

		for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
		{
			interactWithObjects(node);

			if (sf::Keyboard::isKeyPressed((sf::Keyboard::X)) && !AllianceDialogueUI::getInstance().isMenuOpen())
			{
				for(auto& enemy: enemies)
				{
					if(enemy->getCurrentNode() == node && !enemy->GetPlayerAllegiance()->isHostile())
					{
						AllianceDialogueUI::getInstance().OpenMenu();
						enemy->ChangeState(new IdleState(myPlayer));
					}
				}
			}

			transitionToBattleMode(node);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !interactWithObject && !Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen() && !PlayerTabMenu::isMenuOpen())
		{
			interactWithObject = true;
			playerMenu->Interact(myPlayer);
		}

		handleKeyInput();
		myMap->getChunks()[myPlayer->getCurrentChunkID()]->updateIslands(dt);
		//
		if (myPlayer->isOnBoat())
		{
			playerBoat->update(dt);
		}
		else
		{
			myPlayer->update(dt);
		}

		for (auto& enemy : enemies)
		{
			enemy->update(dt);
		}

		if (currentIsland)
		{
			HandleGameObjectCollision();
			HandleBuildingCollision();
		}

		playerMenu->Update();

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

			if (node->GetObject())
				node->GetObject()->render(window);

			if (node->GetBuilding())
				node->GetBuilding()->Render(window);
		}
		if (currentIsland) {
			currentIsland->RenderUI(window);
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
}

void GamePlayScene::processKeys(sf::Event t_event)
{
	//empty
}

void GamePlayScene::processKeyUp(sf::Event t_event)
{
	if (t_event.key.code == sf::Keyboard::R)
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

void GamePlayScene::FindCurrentChunk()
{
	for (auto& chunk : myMap->getChunks())
	{
		if (Utility::collisionWithPoint(myPlayer->getPlayerController()->getPosition(), chunk->getMinVector(), chunk->getMaxVector()))
		{
			myPlayer->setCurrentChunkID(chunk->getChunkID());
		}
		for (auto& enemy : enemies)
		{
			if (Utility::collisionWithPoint(enemy->GetPosition(), chunk->getMinVector(), chunk->getMaxVector()))
			{
				enemy->setCurrentChunkID(chunk->getChunkID());
			}
		}
	}
}

void GamePlayScene::FindCurrentIsland()
{
	auto currentPlayerNode = myPlayer->getCurrentNode();

	for (auto& island : myMap->getChunks()[myPlayer->getCurrentChunkID()]->getIslands()) {

		for (auto& node : island->getLandNodes())
		{
			if (node == currentPlayerNode) {
				currentIsland = island;
			}
		}
	}
}

void GamePlayScene::FindCurrentNodeInSameChunk(int _id, const std::shared_ptr<Enemy>& _enemy) const
{
	for (auto& node : myMap->getChunks()[_id]->nodeGrid)
	{
		if (Utility::collisionWithPoint(myPlayer->getPlayerController()->getPosition(), node->getPosition(), sf::Vector2f(node->getNodeData().size, node->getNodeData().size)))
		{
			if (myPlayer->getCurrentNode() != node)
			{
				myPlayer->setCurrentNode(node);
				myPlayer->updateUpdateableArea(node, 1);
			}
		}
		if (Utility::collisionWithPoint(_enemy->GetPosition(), node->getPosition(), sf::Vector2f(node->getNodeData().size, node->getNodeData().size)))
		{
			if (_enemy->getCurrentNode() != node)
			{
				_enemy->setCurrentNode(node);
				_enemy->updateUpdateableArea(node, 4);
				break;
			}
		}
	}
}

void GamePlayScene::FindCurrentNode() const
{
	for (auto& enemy : enemies)
	{
		if (myPlayer->getCurrentChunkID() == enemy->GetCurrentNodeID())
		{
			FindCurrentNodeInSameChunk(myPlayer->getCurrentChunkID(), enemy);
		}
		else
		{
			FindPlayerCurrentNode();
			FindEnemyCurrentNode(enemy);
		}
	}

}

void GamePlayScene::FindPlayerCurrentNode() const
{
	for (auto& node : myMap->getChunks()[myPlayer->getCurrentChunkID()]->nodeGrid)
	{
		if (Utility::collisionWithPoint(myPlayer->getPlayerController()->getPosition(), node->getPosition(), sf::Vector2f(node->getNodeData().size, node->getNodeData().size)))
		{
			if (myPlayer->getCurrentNode() != node)
			{
				myPlayer->setCurrentNode(node);
				myPlayer->updateUpdateableArea(node, 1);
			}
		}
	}
}

void GamePlayScene::FindEnemyCurrentNode(const std::shared_ptr<Enemy>& _enemy) const
{
	for (auto& node : myMap->getChunks()[_enemy->getCurrentChunkID()]->nodeGrid)
	{
		if (Utility::collisionWithPoint(_enemy->GetPosition(), node->getPosition(), sf::Vector2f(node->getNodeData().size, node->getNodeData().size)))
		{
			if (_enemy->getCurrentNode() != node)
			{
				_enemy->setCurrentNode(node);
				_enemy->updateUpdateableArea(node, 5);
			}
		}
	}
}

void GamePlayScene::HandleGameObjectCollision()
{
	for (auto& object : currentIsland->getGameObjects())
	{
		if (object->GetHitBox().intersects(myPlayer->GetHitBox()))
		{
			myPlayer->getPlayerController()->deflect();
		}
	}
}

void GamePlayScene::HandleBuildingCollision()
{
	for (auto& building : currentIsland->getBuildings())
	{
		if (building->GetHitBox().intersects(myPlayer->GetHitBox()))
		{
			myPlayer->getPlayerController()->deflect();
		}
	}
}

void GamePlayScene::handleKeyInput()
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && keyUp)
		{
			keyUp = false;
			if (!myPlayer->isOnBoat()) {
				for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
				{
					if (node == playerBoat->getDockedNode())
					{
						myPlayer->boardBoat(playerBoat);
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
						FindCurrentNode();
						FindCurrentIsland();
						break;
					}
				}
			}
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
		for (auto& island : myMap->getChunks()[myPlayer->getCurrentChunkID()]->getIslands())
		{
			for (auto& gameObject : island->getGameObjects())
			{
				if (gameObject->getID() == _node->getID())
				{
					gameObject->interact();
					myPlayer->getPlayerController()->setLandVelocity(sf::Vector2f(0, 0));
					currentObjectInteract = gameObject;
					interactWithObject = true;
					break;
				}
			}
		}
		if (interactWithBuildings(_node)) {
			myPlayer->getPlayerController()->setLandVelocity(sf::Vector2f(0, 0));
		}
	}
	
}

bool GamePlayScene::interactWithBuildings(const std::shared_ptr<Node>& _node)
{
	for (auto& island : myMap->getChunks()[myPlayer->getCurrentChunkID()]->getIslands())
	{
		for (auto& building : island->getBuildings())
		{
			for (auto& nodeId : building->GetOccupiedNodeIds())
			{
				if (nodeId == _node->getID())
				{
					building->Interact();
					//currentBuildingInteract = building;
					return true;
				}
			}
		}
	}
	return false;
}

void GamePlayScene::transferInventoryItems()
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(Mouse::getInstance().getMousePosition());
	for (auto& slot : currentObjectInteract.lock()->GetRenderableInventory()->getSlots())
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
