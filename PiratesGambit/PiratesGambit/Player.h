#pragma once
#include"Includes.h"
#include"UpdateableArea.h"
#include"Boat.h"
#include"PlayerController.h"

class Player
{
public:
	Player(bool _onBoat, Boat* _boat, sf::Vector2f _pos) : onBoat(_onBoat), currentBoat(_boat)
	{
		controller = new PlayerController(_pos);

		body.setTexture(TextureManager::getInstance().getTexture("PLAYER_BOAT"));
		body.setOrigin(56, 33);
		body.setScale(0.5, 0.5);

		initCamera();
	}
	~Player() = default;

	void initCamera();

	void update(double dt);
	void render(sf::RenderWindow& window) const;

	void handleKeyInput();

	void updatePosition(const sf::Vector2f& _pos) { body.setPosition(_pos); }

	void setCurrentChunkID(int id_) { currentChunkId = id_; }
	void setCurrentNode(Node*& node_) { currentNode = node_; }

	sf::View getPlayerCamera() const { return playerCamera; }
	int getCurrentChunkID() const { return currentChunkId; }
	Node* getCurrentNode() const { return currentNode; }
	UpdateableArea getUpdateableArea() const { return updateableArea; }
	bool isOnBoat() const { return onBoat; }
	PlayerController* getPlayerController() const { return controller; }

	void updateUpdateableArea(Node*& _startNode, int depth);

	bool checkCollision(Node*& _node, sf::Vector2f& _pos);
	bool boardBoat(Node*& _node);

	//boat logic
	void enterBoat();
	void exitBoat();

private:
	sf::Sprite body;
	PlayerController* controller;

	sf::View playerCamera;

	UpdateableArea updateableArea;
	Node* currentNode{nullptr};

	int currentChunkId{-99};

	Boat* currentBoat;
	bool onBoat{ true };

};