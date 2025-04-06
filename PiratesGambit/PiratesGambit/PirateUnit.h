#pragma once
#include"Includes.h"
#include"Animator.h"
#include "CannonBall.h"
#include "TextureManager.h"
#include"Enums.h"
#include"UnitAmount.h"
#include"ParticleManager.h"
#include"BulletFactory.h"

struct UnitStats
{
	//turn orders
	int initiative;
	float turnPoints = 0;
	bool isActive = true;

	//movement
	int speed;

	//damage calcs
	int stackSize;
	int attackStat;
	int defenceStat;
	int minDamage;
	int maxDamage;
	int health;
};

struct UnitInformation
{
	using IDType = unsigned int;

	static IDType nextID; //tracking unit IDs

	IDType id;
	UnitType unitType;
	UnitName unitName;
	UnitAllegiance allegiance;

	UnitInformation(UnitType type, UnitName name, UnitAllegiance ally)
		: id(nextID++), unitType(type), unitName(name), allegiance(ally) {
	}
};

class PirateUnit
{
public:
	virtual ~PirateUnit() = default;
	PirateUnit(UnitType type, UnitName name, UnitAllegiance allegiance)
		: unitInformation(type, name, allegiance)
	{
		unitAmount = std::make_unique<UnitAmount>();
	}

	void addToCurrentStack(int _amount);
	int getStackSize() const { return unitStats.stackSize; }

	virtual void update(float _dt) = 0;
	virtual void animateSprite(float _dt) = 0;

	void updateUnitAmount(int _amount);
	void placeUnitAmountText();

	void moveUnit(sf::Vector2f _vel);
	void Attack(sf::Vector2f _targetDirection);

	int TakeDamage(int _totalDamage);

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void placeUnit(sf::Vector2f _pos);
	void setCurrentNodeId(int _id) { nodeId = _id; }
	int getCurrentNodeId()const { return nodeId; }
	sf::Vector2f getPosition() const { return sprite.getPosition(); }
	int getSpeed() const { return unitStats.speed; }
	sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
	void setStackSize(int _size) { 
		unitStats.stackSize = _size;
		unitAmount->updateAmount(unitStats.stackSize);
	}

	UnitState currentState = IDLE;

	UnitStats unitStats;

	UnitStats unitBaseStats;

	UnitInformation unitInformation;

protected:
	int facingDirection = 1;
	float scaleX = 3.5, scaleY = 3.5;
	int nodeId;
	sf::Sprite sprite;

	bool attackAnimation = false;
	bool walkAnimation;
	bool idleAnimation;
	bool deathAnimation = false;
	bool damagedAnimation = false;

	AnimationState animationState;

	std::unique_ptr<UnitAmount> unitAmount;
	sf::Vector2f velocity;

	std::vector<std::shared_ptr<CannonBall>> bullets;

	sf::Vector2f targetPosition;

	sf::CircleShape shadow;
};

