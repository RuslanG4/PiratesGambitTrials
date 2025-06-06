#ifndef ENEMY_H
#define ENEMY_H
#include"Includes.h"
#include"UpdateableArea.h"
#include "Node.h"
#include "HitBox.h"
#include "Enums.h"
#include"Army.h"
#include "EnemyBoat.h"
#include "EnemyBoatWander.h"
#include "EnemyState.h"
#include "EnemyUI.h"
#include "IdleState.h"
#include"Structs.h"
#include "Player.h"
#include "PlayerAllegiance.h"

class EnemyBoat; //forward ref

class Enemy
{
public:
	Enemy(const std::shared_ptr<Player>& _playerRef, int _enemyID, UnitAllegiance _allegiance)
	{
		army = std::make_unique<Army>();
		updateableArea = std::make_unique<UpdateableArea>();

		enemyID = _enemyID;
		enemyAllegiance = _allegiance;

		setFactionAllegiance();

		body.setTexture(TextureManager::getInstance().getTexture("PIRATE_CAPTAIN"));

		sf::IntRect rectSourceSprite;
		rectSourceSprite.height = 32;
		rectSourceSprite.width = 32;
		rectSourceSprite.left = 0;
		rectSourceSprite.top = 0;
		body.setTextureRect(rectSourceSprite);

		body.setOrigin(16, 24);
		body.setScale(2, 2);

		currentDirection = static_cast<EnemyDirection>(rand() % 4);

		myHitbox = new HitBox(sf::Vector2f(22, 22));

		enemyUI = std::make_unique<EnemyUI>(100, 10);

		ChangeState(new EnemyBoatWander(_playerRef));
	}
	~Enemy() = default;

	void update(double dt);
	void render(const std::unique_ptr<sf::RenderWindow>& window) const;

	void setCurrentChunkID(int id_) { currentChunkId = id_; }

	//animation
	void handleAnimationStates(double dt);
	void SetAnimationState(UnitState _newState) { currentState = _newState; }

	//Global Bounds;
	sf::FloatRect GetGlobalBounds() const;

	//Updating position
	void setCurrentNode(const std::shared_ptr<Node>& node_) { currentNode = node_; }
	void SetPosition(sf::Vector2f _pos);
	void FacePlayer(int _direction)
	{
		body.setScale(_direction, scaleY);
	}
	void updateUpdateableArea(const std::shared_ptr<Node>& _startNode, int depth) const;
	void FaceDirection(sf::Vector2f _pos);
	//

	void UpdateDirection(sf::Vector2f _direction);
	EnemyDirection GetDirection() const { return currentDirection; }
	void ChangeDirection(EnemyDirection _direction) { currentDirection = _direction; }

	sf::Vector2f GetPosition() const { return body.getPosition(); }
	int GetCurrentNodeID() const { return currentNodeId; }
	int getCurrentChunkID() const { return currentChunkId; }
	const std::shared_ptr<Node>& getCurrentNode() const { return currentNode; }
	const std::unique_ptr<UpdateableArea>& getUpdateableArea() const { return updateableArea; }

	//boat interaction functions
	void boardBoat(const std::shared_ptr<EnemyBoat>& _boat);
	void disembarkBoat(const std::shared_ptr<Node>& _node);
	bool isOnBoat() const { return onBoat; }
	void markForDeath() { drowned = true; }
	bool isAlive() const { return !drowned; }
	std::shared_ptr<EnemyBoat> GetBoat() const { return boatRef; }

	//Army
	const std::unique_ptr<Army>& getArmy() const { return army; }
	void LoseArmy();

	void ChangeState(EnemyState* newState);
	EnemyState* GetCurrentState() const { return currentActionState; }


	void setFactionAllegiance();
	std::string GetFactionAllegiance() { return factionAllegiance; }
	int GetEnemyID() const { return enemyID; }
	std::string GetEnemyAllegiance() const;
	UnitAllegiance GetEnemyTeam() const { return enemyAllegiance; }

	void setPirateName(const std::string& _name) { pirateName = _name; }

	void setAllegiance(const int& _value) { 
		playerAllegiance.setAllegiance(_value); 
		enemyUI->updateAllegiance(playerAllegiance);
	}
	void updateAllegiance(const int& _value) {
		playerAllegiance.changeAllegiance(_value);
		enemyUI->updateAllegiance(playerAllegiance);
	}
	PlayerAllegiance GetPlayerAllegiance() const{
		return playerAllegiance;
	}
	void updateEnemyAllegiance(const int& _value);

	std::string GetPirateName() const { return pirateName; }

	std::vector<std::shared_ptr<Enemy>>& GetSurroundingEnemies() { return surroundingEnemies; }
	void ClearSurroundingEnemies() { surroundingEnemies.clear(); }
	void AddToSurroundingEnemies(const std::shared_ptr<Enemy>& _enemy) { surroundingEnemies.push_back(_enemy); };

	void updateHiredStatus(bool _value) { isHired = _value; }
	bool getHiredStatus() const { return isHired; }

	void UpdateLeader(bool _value) { isLeader = _value; }
	bool getIsLeader() const { return isLeader; }

	void updateFollowing(bool _value) { isFollowing = _value; }
	bool getIsFollowing() const { return isFollowing; }
private:
	sf::Sprite body;
	std::string factionAllegiance = "";

	PlayerAllegiance playerAllegiance;
	std::unique_ptr<EnemyUI> enemyUI;

	EnemyState* currentActionState;
	AnimationState animationState;
	UnitState currentState = UnitState::IDLE; //animation state

	HitBox* myHitbox; //hitbox for collisions

	std::unique_ptr<UpdateableArea> updateableArea; 

	std::shared_ptr<Node> currentNode{ nullptr };

	std::vector<std::shared_ptr<Node>> path;

	std::unique_ptr<Army> army;

	EnemyDirection currentDirection;

	std::vector<std::shared_ptr<Enemy>> surroundingEnemies;

	int scaleX = 2;
	int scaleY = 2;

	int currentChunkId{ -99 };
	int currentNodeId{ 0 };

	//animation
	bool idleAnimation{ false };
	bool walkAnimation{ false };

	//Boat
	std::shared_ptr<EnemyBoat> boatRef;
	bool onBoat{ false };
	bool drowned{ false };

	//ID
	int enemyID;

	//Name
	std::string pirateName;

	//Enemy Allegiance
	UnitAllegiance enemyAllegiance;
	bool isHired{ false };


	bool isLeader{ false };
	bool isFollowing{ false };
};

#endif 

