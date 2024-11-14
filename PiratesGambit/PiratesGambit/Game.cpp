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

	myMap = new FullMap(m_window, 3); //keep 1x1, 2x2

	playerBoat = new Boat();
	myPlayer = std::make_unique<Player>(true, playerBoat, sf::Vector2f(25,25));

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
		}
		if(sf::Event::KeyReleased == newEvent.type)
		{
			processKeyUp(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if(t_event.key.code == sf::Keyboard::S)
	{
		keyUp = false;
	}
}

void Game::processKeyUp(sf::Event t_event)
{
	//if(t_event.key.code == sf::Keyboard::S)
	//{
	//	//sf::Texture texture;
	///*	texture.create(CHUNK_NODE_ROWS * 5 * 24, CHUNK_NODE_COLS * 5 * 24);
	//	texture.update(m_window);  */
	//	sf::Image screenshot = windowCapture.getTexture().copyToImage();  
	//	screenshot.saveToFile("ASSETS\\screenshot.png");  
	//}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	myPlayer->update(t_deltaTime.asMilliseconds());

	updateVisableNodes();
	findCurrentChunk();
	findCurrentNode();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.setView(myPlayer->getPlayerCamera());
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
		if (Utility::collision(myPlayer->getPlayerController()->getPosition(), chunk->getMinVector(), chunk->getMaxVector()))
		{
			myPlayer->setCurrentChunkID(chunk->getChunkID());
		}
	}
}

void Game::findCurrentNode()
{
	for (auto node : myMap->getChunks()[myPlayer->getCurrentChunkID()]->nodeGrid)
	{
		if (Utility::collision(myPlayer->getPlayerController()->getPosition(), node->getPosition(), sf::Vector2f(node->getPosition().x + node->getSize(), node->getPosition().y + node->getSize())))
		{
			if (myPlayer->getCurrentNode() != node)
			{
				myPlayer->setCurrentNode(node);
				myPlayer->updateUpdateableArea(node, 2);
			}
		}
	}
}

void Game::updateVisableNodes()
{
	sf::FloatRect viewBounds(myPlayer->getPlayerCamera().getCenter() - myPlayer->getPlayerCamera().getSize() / 2.0f, myPlayer->getPlayerCamera().getSize());

	int minX = std::max(0, static_cast<int>(viewBounds.left / 24));
	int maxX = std::min(24 * 3 - 1, static_cast<int>((viewBounds.left + viewBounds.width) / 24));
	int minY = std::max(0, static_cast<int>(viewBounds.top / 24));
	int maxY = std::min(24 * 3 - 1, static_cast<int>((viewBounds.top + viewBounds.height) / 24));

	std::set<int> newVisibleNodes;

	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			int index = y * (24 * 3) + x;
			newVisibleNodes.insert(index);
		}
	}

	visibleNodes = std::move(newVisibleNodes);
}

