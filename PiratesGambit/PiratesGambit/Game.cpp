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
	if (!TextureManager::getInstance().loadAllResources()) {
		std::cerr << "Failed to load all resources!";
	}
	SceneManager::getInstance().setScene(new MainMenuScene());
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
			processEvents();
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
		SceneManager::getInstance().getCurrentScene()->handleInput(m_window, newEvent);
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			Mouse::getInstance().processMouseUp(newEvent);
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(double t_deltaTime)
{
	Mouse::getInstance().update(m_window);
	SceneManager::getInstance().getCurrentScene()->update(t_deltaTime);
	ParticleManager::getInstance().update(t_deltaTime);
	BulletFactory::getInstance().update();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window->clear(sf::Color::Black);
	SceneManager::getInstance().getCurrentScene()->render(m_window);
	ParticleManager::getInstance().render(m_window);
	m_window->display();
}


