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

	myMap = new FullMap(m_window, textureManager, 3); //keep 1x1, 2x2

	myPlayer.setSprite(textureManager.getTexture("PLAYER"));

	windowCapture.create(CHUNK_NODE_ROWS * 3 * 24, CHUNK_NODE_COLS * 3 * 24);
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
	if(t_event.key.code == sf::Keyboard::S)
	{
		//sf::Texture texture;
	/*	texture.create(CHUNK_NODE_ROWS * 5 * 24, CHUNK_NODE_COLS * 5 * 24);
		texture.update(m_window);  */
		sf::Image screenshot = windowCapture.getTexture().copyToImage();  
		screenshot.saveToFile("ASSETS\\screenshot.png");  
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	myPlayer.update(t_deltaTime.asMilliseconds());
	for(auto chunk : myMap->getChunks())
	{
		if(collision(myPlayer.getPosition(), chunk->getMinVector(), chunk->getMaxVector()))
		{
			myPlayer.setCurrentChunkID(chunk->getChunkID());
		}
	}
	for(auto node : myMap->getChunks()[myPlayer.getCurrentChunkID()]->nodeGrid)
	{
		if(collision(myPlayer.getPosition(),node->getPosition(), sf::Vector2f(node->getPosition().x + node->getSize(), node->getPosition().y + node->getSize())))
		{
			if(currentNode != node)
			{
				currentNode = node;
				searchLocalArea(currentNode, 2);
			}
		}
	}

	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	//m_window.setView(myPlayer.getPlayerCamera());
	m_window.clear(sf::Color::Black);
	if (!windowTexture)
	{
	for(auto chunk : myMap->getChunks())
	{
		for(auto node: chunk->nodeGrid)
		{
			if (node->waterBackSprite && node->drawableNode) {
				windowCapture.draw(*(node->waterBackSprite));
				windowCapture.draw(*(node->drawableNode));
			}
		}
	}
		windowCapture.display();
		saveTexture();
	}
	m_window.draw(wholeMap);
	for(auto node : updateArea)
	{
		if (node != nullptr) {
			m_window.draw(node->debugShape);
		}
	}
	/*myMap->getChunks()[myPlayer.getCurrentChunkID()]->drawGrid(m_window);*/

	myPlayer.render(m_window);
	m_window.display();
}

void Game::initialise()
{
	if (!font.loadFromFile(FONT_PATH))
	{
		std::cout << "error loading font";
	}
}

bool Game::collision(sf::Vector2f v1, sf::Vector2f v2Min, sf::Vector2f v2Max)
{
	return v1.x > v2Min.x && v1.x < v2Max.x && v1.y > v2Min.y && v1.y < v2Max.y;
}

void Game::searchLocalArea(Node*& _startNode, int depth)
{
	for (Node* node : updateArea) {
		if (node != nullptr) {
			node->debugShape.setFillColor(sf::Color::Transparent);
		}
	}
	updateArea.clear();

	int iterations = (1 + 2 * depth) * (1 + 2 * depth);
	int iterCount = 1;

	std::queue <Node*> nodeQueue;

	nodeQueue.push(_startNode);
	nodeQueue.front()->updating = true;
	updateArea.push_back(_startNode);
	nodeQueue.front()->debugShape.setFillColor(sf::Color(123, 123, 123, 180));

	while (iterCount < iterations)
	{

		auto neighbours = nodeQueue.front()->getNeighbours();
		for (auto neighbour : neighbours)
		{
			if (neighbour->updating == false && iterCount < iterations)
			{
				neighbour->updating = true;
				neighbour->debugShape.setFillColor(sf::Color(123, 123, 123, 180));
				iterCount++;
				updateArea.push_back(neighbour);
				nodeQueue.push(neighbour);
			}
		}
		nodeQueue.pop();
	}
	for (Node* node : updateArea) {
		node->updating = false;
	}
}

void Game::saveTexture()
{
	wholeMap.setTexture(windowCapture.getTexture());
	windowTexture = true;
	for (auto chunk : myMap->getChunks())
	{
		chunk->deleteSprites();
	}
}

