#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include"Constants.h"
#include"Grid.h"
#include"FullMap.h"
#include "Player.h"
#include"Boat.h"
#include"Camera.h"

#include"Barrel.h"
#include"Mouse.h"

#include "BattleScene.h"


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
	void update(double t_deltaTime);
	void render();
	void initialise();

	void findCurrentNode();
	void findCurrentChunk();

	void handleKeyInput();

	void interactWithObjects();

	void transferInventoryItems();

	void updateVisableNodes();
	std::set<int> visibleNodes;

	bool keyUp = true;
	bool interactWithObject = false;

	sf::Sprite m_appleSprite;
	sf::Texture m_appleTexture;

	sf::RenderWindow m_window; // main SFML window
	sf::Font font;

	std::set<Node*> updateArea{nullptr};

	Node* currentNode;
	
	std::unique_ptr<FullMap> myMap;
	std::shared_ptr<Player> myPlayer;
	std::shared_ptr<Boat> playerBoat;

	Camera myCamera;

	std::weak_ptr<GameObject> currentObjectInteract;

	//battle scene
	std::unique_ptr<BattleScene> battleScene;
	bool battle = true;

};

#endif // !GAME_HPP