#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include"Constants.h"
#include"Grid.h"
#include"FullMap.h"
#include "Player.h"


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
	void processKeys(sf::Event t_event);
	void processKeyUp(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void initialise();

	void findCurrentNode();
	void findCurrentChunk();

	void updateVisableNodes();
	std::set<int> visibleNodes;

	bool keyUp = true;

	sf::Sprite m_appleSprite;
	sf::Texture m_appleTexture;

	sf::RenderWindow m_window; // main SFML window
	sf::Font font;

	std::set<Node*> updateArea{nullptr};

	Node* currentNode;
	
	FullMap* myMap;
	std::unique_ptr<Player> myPlayer;

	Boat* playerBoat;
};

#endif // !GAME_HPP