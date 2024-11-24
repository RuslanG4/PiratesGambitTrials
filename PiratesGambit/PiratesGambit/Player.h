#ifndef PLAYER_H
#define PLAYER_H
#include"Includes.h"
#include"UpdateableArea.h"
#include"PlayerController.h"
#include "Node.h"
#include "HitBox.h"
#include "Inventory.h"

class Boat;

enum PlayerState
{
	IDLE,
	WALK
};

class Player
{
public:
	Player(sf::Vector2f _pos)
	{
		controller = new PlayerController(_pos);
		inventory = std::make_unique<Inventory>();

		//inventory = new Inventory();

		body.setTexture(TextureManager::getInstance().getTexture("PIRATE_CAPTAIN"));

		sf::IntRect rectSourceSprite;
		rectSourceSprite.height = 32;
		rectSourceSprite.width = 32;
		rectSourceSprite.left = 0;
		rectSourceSprite.top = 0;
		body.setTextureRect(rectSourceSprite);
		
		body.setOrigin(16, 24);
		body.setScale(2, 2);

		myHitbox = new HitBox(sf::Vector2f(22, 22));
	}
	~Player() = default;

	void update(double dt);
	void render(sf::RenderWindow& window) const;

	void handlePlayerStates();
	void animatePlayer(int _colAmt, int _rowNum);
	void updatePlayerState();

	void updatePosition(const sf::Vector2f& _pos) { body.setPosition(_pos); }

	void setCurrentChunkID(int id_) { currentChunkId = id_; }
	void setCurrentNode(Node*& node_) { currentNode = node_; }

	int getCurrentChunkID() const { return currentChunkId; }
	Node* getCurrentNode() const { return currentNode; }
	UpdateableArea getUpdateableArea() const { return updateableArea; }
	bool isOnBoat() const { return onBoat; }
	PlayerController* getPlayerController() const { return controller; }
	//Inventory
	const std::unique_ptr<Inventory>& getInventory() const { return inventory; }

	void updateUpdateableArea(Node*& _startNode, int depth);

	bool checkCollision(Node*& _node, sf::Vector2f& _pos);

	void boardBoat(std::shared_ptr<Boat>& _boat);
	void disembarkBoat(Node* _node);

private:
	sf::Sprite body;

	PlayerController* controller;
	PlayerState currentState = PlayerState::IDLE;

	std::unique_ptr<Inventory> inventory;

	HitBox* myHitbox;

	UpdateableArea updateableArea;
	Node* currentNode{nullptr};

	int currentChunkId{-99};

	int animateTime = 0;
	int currentFrame = 0;

	std::weak_ptr<Boat> currentBoat;
	bool onBoat{ true };

};

#endif // PLAYER_H