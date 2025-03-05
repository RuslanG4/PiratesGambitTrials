#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "MainMenuScene.h"
#include "SceneManager.h"
#include "BulletFactory.h"
#include "ParticleManager.h"
#include "TextureManager.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:
	void processEvents();
	void update(double t_deltaTime);
	void render();

	std::unique_ptr<sf::RenderWindow> m_window;
};

#endif // !GAME_HPP