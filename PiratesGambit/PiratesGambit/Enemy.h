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
#include "EnemyState.h"
#include "IdleState.h"
#include"Structs.h"
#include"PathFindingFunctions.h"
#include "Player.h"

class Boat; //forward ref

class Enemy
{
public:
	Enemy(sf::Vector2f _pos, const std::shared_ptr<Player> _playerRef)
	{
		army = std::make_unique<Army>();
		updateableArea = std::make_unique<UpdateableArea>();

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

		ChangeState(new IdleState(_playerRef));
	}
	~Enemy() = default;

	void update(double dt);
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	void setCurrentChunkID(int id_) { currentChunkId = id_; }

	//animation
	void handleAnimationStates(double dt);
	void SetAnimationState(UnitState _newState) { currentState = _newState; }

	//Global Bounds;
	sf::FloatRect GetGlobalBounds() const { return myHitbox->GetGlobalBounds(); }

	//Updating position
	void updatePosition(const sf::Vector2f& _pos);
	void setCurrentNode(const std::shared_ptr<Node>& node_) { currentNode = node_; }
	void SetPosition(sf::Vector2f _pos)
	{
		body.setPosition(_pos);
		myHitbox->setPosition(_pos);
	}
	void FacePlayer(int _direction)
	{
		body.setScale(_direction, scaleY);
	}
	void updateUpdateableArea(const std::shared_ptr<Node>& _startNode, int depth) const; 
	//

	sf::Vector2f GetPosition() const { return body.getPosition(); }
	int GetCurrentNodeID() const { return currentNodeId; }
	int getCurrentChunkID() const { return currentChunkId; }
	const std::shared_ptr<Node>& getCurrentNode() const { return currentNode; }
	const std::unique_ptr<UpdateableArea>& getUpdateableArea() const { return updateableArea; }

	//boat interaction functions
	void boardBoat(const std::shared_ptr<Boat>& _boat);
	void disembarkBoat(const std::shared_ptr<Node>& _node);
	bool isOnBoat() const { return onBoat; }

	//Army
	const std::unique_ptr<Army>& getArmy() const { return army; }

	void ChangeState(EnemyState* newState);

private:
	sf::Sprite body;

	EnemyState* currentActionState;
	AnimationState animationState;
	UnitState currentState = UnitState::IDLE; //animation state

	HitBox* myHitbox; //hitbox for collisions

	std::unique_ptr<UpdateableArea> updateableArea; 

	std::shared_ptr<Node> currentNode{ nullptr };

	std::vector<std::shared_ptr<Node>> path;

	std::unique_ptr<Army> army;

	int scaleX = 2;
	int scaleY = 2;

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

