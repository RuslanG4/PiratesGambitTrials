#ifndef ENEMY_H
#define ENEMY_H
#include"Includes.h"
#include"UpdateableArea.h"
#include "Node.h"
#include "HitBox.h"
#include "Inventory.h"
#include "Animator.h"
#include "Enums.h"
#include"Army.h"
#include"Structs.h"

class Boat; //forward ref

class Enemy
{
public:
	Enemy(sf::Vector2f _pos)
	{
		army = std::make_unique<Army>();

		army->addUnit(std::make_shared<Buccaneer>(23,YELLOW_PLAYER));
		army->addUnit(std::make_shared<Gunner>(16,YELLOW_PLAYER));


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
	~Enemy() = default;

	void update(double dt);
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	//animation
	void handleAnimationStates(double dt);

	//Global Bounds;
	sf::FloatRect GetGlobalBounds() const { return body.getGlobalBounds(); }

	//Updating position
	void updatePosition(const sf::Vector2f& _pos) { body.setPosition(_pos); }
	void setCurrentNode(int _id) { currentNodeId = _id; }

	//
	int GetCurrentNodeID() const { return currentNodeId; }

	//boat interaction functions
	void boardBoat(const std::shared_ptr<Boat>& _boat);
	void disembarkBoat(const std::shared_ptr<Node>& _node);
	bool isOnBoat() const { return onBoat; }

	//Army
	const std::unique_ptr<Army>& getArmy() const { return army; }

private:
	sf::Sprite body;

	AnimationState animationState;
	UnitState currentState = UnitState::IDLE; //animation state

	HitBox* myHitbox; //hitbox for collisions

	std::shared_ptr<Node> currentNode{ nullptr };

	std::unique_ptr<Army> army;

	int currentChunkId{ -99 };
	int currentNodeId{ 0 };

	//animation
	bool idleAnimation{ false };
	bool walkAnimation{ false };

	//Boat
	std::weak_ptr<Boat> currentBoat;
	bool onBoat{ false };

};

#endif 

