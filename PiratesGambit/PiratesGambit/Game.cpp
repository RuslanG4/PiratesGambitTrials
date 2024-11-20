#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH,SCREEN_HEIGHT, 32U }, "SFML Game" }
{
	initialise();

	myMap = new FullMap(m_window, 1); //keep 1x1, 2x2

	myPlayer = std::make_shared<Player>(sf::Vector2f(25, 25));

	playerBoat = std::make_shared<Boat>(sf::Vector2f(25, 25), myPlayer);

	myPlayer->boardBoat(playerBoat);

	playerBoat->addCannonBall();
	

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
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
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
	while (m_window.pollEvent(newEvent))
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
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	updateVisableNodes();
	findCurrentChunk();
	findCurrentNode();

	handleKeyInput();
	//
	if(myPlayer->isOnBoat())
	{
		playerBoat->update(t_deltaTime.asMilliseconds());
	}else
	{
		myPlayer->update(t_deltaTime.asMilliseconds());
	}
	
	myCamera.setCameraCenter(myPlayer->getPlayerController()->getPosition());

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.setView(myCamera.getCamera());
	m_window.clear(sf::Color::Black);

	for (int index : visibleNodes) {
		Node* node = myMap->getFullMap()[index];

		m_window.draw(*(node->waterBackSprite));
		m_window.draw(*(node->drawableNode));
	}
	
	myPlayer->render(m_window);
	playerBoat->render(m_window);

	m_window.display();
}

void Game::initialise()
{
	if (!font.loadFromFile(FONT_PATH))
	{
		std::cout << "error loading font";
	}
}

void Game::findCurrentChunk()
{
	for (auto chunk : myMap->getChunks())
	{
		if (Utility::collisionWithPoint(myPlayer->getPlayerController()->getPosition(), chunk->getMinVector(), chunk->getMaxVector()))
		{
			myPlayer->setCurrentChunkID(chunk->getChunkID());
		}
	}
}

void Game::handleKeyInput()
{
	sf::Vector2f desiredVelocity{ 0,0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if(myPlayer->isOnBoat())
		{
			playerBoat->getController()->increaseSpeed();
		}else
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
			for (auto& node : myPlayer->getUpdateableArea().getUpdateableNodes())
			{
				if (node == playerBoat->getDockedNode())
				{
					myPlayer->boardBoat(playerBoat);
				}
			}
		}
		else
		{
			for (auto& node : myPlayer->getUpdateableArea().getUpdateableNodes())
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

void Game::findCurrentNode()
{
	for (auto node : myMap->getChunks()[myPlayer->getCurrentChunkID()]->nodeGrid)
	{
		if (Utility::collisionWithPoint(myPlayer->getPlayerController()->getPosition(), node->getPosition(), sf::Vector2f(node->getPosition().x + node->getSize(), node->getPosition().y + node->getSize())))
		{
			if (myPlayer->getCurrentNode() != node)
			{
				myPlayer->setCurrentNode(node);
				myPlayer->updateUpdateableArea(node, 1);
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

