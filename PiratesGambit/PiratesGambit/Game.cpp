#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game()
{
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode( SCREEN_WIDTH,SCREEN_HEIGHT), 32U );
	initialise();

	myPlayer = std::make_shared<Player>(sf::Vector2f(25, 25));

	playerMenu = std::make_unique<PlayerTabMenu>(myPlayer->getArmy(), myPlayer->getInventory());

	myMap = std::make_unique<FullMap>(m_window, 1, myPlayer); //keep 1x1, 2x2

	enemy = std::make_shared<Enemy>(sf::Vector2f(25, 25));

	playerBoat = std::make_shared<Boat>(sf::Vector2f(25, 25), myPlayer);

	myPlayer->boardBoat(playerBoat);

	playerBoat->addCannonBall();

	findCurrentChunk();

	battleScene = std::make_unique<BattleScene>(myPlayer, enemy);

	myMap->getChunks()[0]->getIslands()[0]->PlaceEnemy(enemy);

	//myPlayer->setSprite(textureManager.getTexture("PLAYER_BOAT"));
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}



/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window->isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame.asMilliseconds()); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window->pollEvent(newEvent))
	{
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
			if (myPlayer->isOnBoat()) {
				playerBoat->processKeys(newEvent);
			}
		}
		if(sf::Event::KeyReleased == newEvent.type)
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
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			Mouse::getInstance().processMouseUp(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	
}

void Game::processKeyUp(sf::Event t_event)
{
	if(t_event.key.code == sf::Keyboard::R)
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

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(double t_deltaTime)
{
	Mouse::getInstance().update(m_window);
	ParticleManager::getInstance().update(t_deltaTime);
	BulletFactory::getInstance().update();
	if (!battle && !battleTransition.IsTransitionActive()) {
		updateVisableNodes();
		findCurrentChunk();
		findCurrentNode();

		handleKeyInput();
		myMap->getChunks()[myPlayer->getCurrentChunkID()]->updateIslands(t_deltaTime);
		//
		if (myPlayer->isOnBoat())
		{
			playerBoat->update(t_deltaTime);
		}
		else
		{
			myPlayer->update(t_deltaTime);
		}

		playerMenu->Update();

		enemy->update(t_deltaTime);

		transitionToBattleMode();

		myCamera.setCameraCenter(myPlayer->getPlayerController()->getPosition());
	}
	else if(battleTransition.IsTransitionActive())
	{
		battleTransition.Update();
		if(battleTransition.IsTransitionActive() == false)
		{
			battle = true;
		}

	}
	else {
		battleScene->update(t_deltaTime);
		Mouse::getInstance().update(m_window);
	}

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window->clear(sf::Color::Black);
	if (!battle) {
		m_window->setView(myCamera.getCamera());

		for (int index : visibleNodes) {
			std::shared_ptr<Node> node = myMap->getFullMap()[index];

			m_window->draw(*(node->waterBackSprite));
			m_window->draw(*(node->drawableNode));
		}

		myPlayer->render(m_window);
		
		playerBoat->render(m_window);

		enemy->render(m_window);

		myMap->getChunks()[myPlayer->getCurrentChunkID()]->drawGameObject(m_window);
		playerMenu->Render(m_window);
	}else
	{
		battleScene->render(m_window);
	}

	ParticleManager::getInstance().render(m_window);

	battleTransition.Render(m_window);
	m_window->display();
}

void Game::initialise()
{

}

void Game::findCurrentChunk()
{
	for (auto& chunk : myMap->getChunks())
	{
		if (Utility::collisionWithPoint(myPlayer->getPlayerController()->getPosition(), chunk->getMinVector(), chunk->getMaxVector()))
		{
			myPlayer->setCurrentChunkID(chunk->getChunkID());
		}
	}
}

void Game::handleKeyInput()
{
	if (!Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen()) {
		sf::Vector2f desiredVelocity{ 0,0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
						playerBoat->setDockedNode(node);
					}
				}
			}
		}
	}

	//Chnage this to general boolean to look clanaer
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::E)) && !interactWithObject && !Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen() && !PlayerTabMenu::isMenuOpen() )
	{
		interactWithObject = true;
		interactWithObjects();
		if (interactWithBuildings()) {
			myPlayer->getPlayerController()->setLandVelocity(sf::Vector2f(0, 0));
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !interactWithObject && !Inventory::isInventoryOpen() && !HireRecruitUI::IsUIOpen() && !PlayerTabMenu::isMenuOpen())
	{
		interactWithObject = true;
		playerMenu->Interact(myPlayer);
	}
}

void Game::transitionToBattleMode()
{
	for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
	{
		if(node->getID() == enemy->GetCurrentNodeID())
		{
			if(enemy->GetGlobalBounds().intersects(myPlayer->GetHitBox()))
			{
				battleTransition.startTransition(1);
			}
		}
	}
}

void Game::interactWithObjects()
{
	for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
	{
		for(auto& island : myMap->getChunks()[myPlayer->getCurrentChunkID()]->getIslands())
		{
			for(auto& gameObject: island->getGameObjects())
			{
				if (gameObject->getID() == node->getID())
				{
					gameObject->interact();
					currentObjectInteract = gameObject;
				}
			}
		}
	}
}

bool Game::interactWithBuildings()
{
	for (auto& node : myPlayer->getUpdateableArea()->getUpdateableNodes())
	{
		for (auto& island : myMap->getChunks()[myPlayer->getCurrentChunkID()]->getIslands())
		{
			for (auto& building : island->getBuildings())
			{
				for(auto& nodeId : building->GetOccupiedNodeIds())
				{
					if(nodeId == node->getID())
					{
						building->Interact();
						currentBuildingInteract = building;
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Game::transferInventoryItems()
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

void Game::findCurrentNode()
{
	for (auto& node : myMap->getChunks()[myPlayer->getCurrentChunkID()]->nodeGrid)
	{
		if (Utility::collisionWithPoint(myPlayer->getPlayerController()->getPosition(), node->getPosition(), sf::Vector2f(node->getSize() , node->getSize())))
		{
			if (myPlayer->getCurrentNode() != node)
			{
				
				myPlayer->setCurrentNode(node);
				auto a = myPlayer->getCurrentNode()->getID();
				myPlayer->updateUpdateableArea(node, 1);
				std::cout << myPlayer->getCurrentNode()->getID() << "\n";
			}
		}
	}
}

void Game::updateVisableNodes()
{
	sf::FloatRect viewBounds(myCamera.getCamera().getCenter() - myCamera.getCamera().getSize() / 2.0f, myCamera.getCamera().getSize());

	int minX = std::max(0, static_cast<int>(viewBounds.left / 32));
	int maxX = std::min(32 * 1 - 1, static_cast<int>((viewBounds.left + viewBounds.width) / 32));
	int minY = std::max(0, static_cast<int>(viewBounds.top / 32));
	int maxY = std::min(32 * 1 - 1, static_cast<int>((viewBounds.top + viewBounds.height) / 32));

	std::set<int> newVisibleNodes;

	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			int index = y * (32 * 1) + x;
			newVisibleNodes.insert(index);
		}
	}

	visibleNodes = std::move(newVisibleNodes);
}

