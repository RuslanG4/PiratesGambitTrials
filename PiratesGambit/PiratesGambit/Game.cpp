#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game" }
{
	initialise();
	myGrid = new Grid(68,font);

	myGrid->ApplyCellular(5, m_window);

	windowCapture.create(1600, 1080);
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
		//texture.create(m_window.getSize().x, m_window.getSize().y);  
		//texture.update(m_window);  
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
	//myGrid->collapse(m_window);
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	myGrid->drawGrid(m_window);
	for(auto node : myGrid->nodeGrid)
	{
		windowCapture.draw(node->drawableNode);
	}
	windowCapture.display();
	m_window.display();
}

void Game::initialise()
{
	if (!font.loadFromFile(FONT_PATH))
	{
		std::cout << "error loading font";
	}
}