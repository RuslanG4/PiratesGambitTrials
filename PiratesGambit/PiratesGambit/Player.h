#ifndef PLAYER_H
#define PLAYER_H
#include"Includes.h"
#include"UpdateableArea.h"
#include"PlayerController.h"
#include "Node.h"
#include "HitBox.h"
#include "Inventory.h"
#include "Enums.h"
#include"Army.h"
#include "Coins.h"
#include"Structs.h"


class Boat; //forward ref

class Player
{
public:
	Player(sf::Vector2f _pos)
	{
		controller = new PlayerController(_pos);
		inventory = std::make_unique<Inventory>();
		updateableArea = std::make_unique<UpdateableArea>();
		playerArmy = std::make_unique<Army>();

		playerArmy->addUnit(std::make_shared<Buccaneer>(12,RED_PLAYER));
		playerArmy->addUnit(std::make_shared<Gunner>(26, RED_PLAYER));
		playerArmy->addUnit(std::make_shared<Harpooner>(6, RED_PLAYER));

		inventory->addItem(std::make_unique<Coins>(50000));

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
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	//animation
	void handlePlayerStates(double dt);
	void updatePlayerState();

	//Current Node + chunk
	void setCurrentChunkID(int id_) { currentChunkId = id_; }
	void setCurrentNode(const std::shared_ptr<Node>& node_) { currentNode = node_; }
	int getCurrentChunkID() const { return currentChunkId; }
	const std::shared_ptr<Node>& getCurrentNode() const { return currentNode; }
	
	//player controller
	PlayerController* getPlayerController() const { return controller; }
	void updatePosition(const sf::Vector2f& _pos) { body.setPosition(_pos); }

	//Inventory
	const std::unique_ptr<Inventory>& getInventory() const { return inventory; }

	//update area
	void updateUpdateableArea(const std::shared_ptr<Node>& _startNode, int depth) const;
	const std::unique_ptr<UpdateableArea>& getUpdateableArea() const { return updateableArea; }

	//land collision
	bool checkCollision(const std::shared_ptr<Node>& _node, sf::Vector2f& _pos);

	//boat interaction functions
	void boardBoat(const std::shared_ptr<Boat>& _boat);
	void disembarkBoat(const std::shared_ptr<Node>& _node);
	bool isOnBoat() const { return onBoat; }

	//Army
	const std::unique_ptr<Army>& getArmy() const { return playerArmy; }

	//HitBox
	sf::FloatRect GetHitBox() const { return myHitbox->GetGlobalBounds(); }

private:
	sf::Sprite body;
	AnimationState animationState;

	PlayerController* controller; //control player
	UnitState currentState = UnitState::IDLE; //animation state

	std::unique_ptr<Inventory> inventory; //player inventory

	HitBox* myHitbox; //hitbox for collisions

	std::unique_ptr<UpdateableArea> updateableArea; //update area around player
	std::shared_ptr<Node> currentNode{nullptr};

	std::unique_ptr<Army> playerArmy;

	int currentChunkId{-99};

	//animation
	int animateTime = 0;
	int currentFrame = 0;

	//Boat
	std::weak_ptr<Boat> currentBoat;
	bool onBoat{ true };

	bool idleAnimation;
	bool walkAnimation;

};

#endif // PLAYER_H