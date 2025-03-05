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
	float speed;

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
	UnitType unitType;
	UnitName unitName;
	UnitAllegiance allegiance;
};

class PirateUnit
{
public:
	virtual ~PirateUnit() = default;
	PirateUnit() = default;

	void addToCurrentStack(int _amount);
	int getStackSize() const { return unitStats.stackSize; }

	virtual void update(float _dt) = 0;
	virtual void animateSprite(float _dt) = 0;

	void updateUnitAmount(int _amount);
	void placeUnitAmountText();

	void moveUnit(sf::Vector2f _vel);
	void Attack(sf::Vector2f _targetDirection);

	void TakeDamage(int _totalDamage);

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void placeUnit(sf::Vector2f _pos);
	void setCurrentNodeId(int _id) { nodeId = _id; }
	int getCurrentNodeId()const { return nodeId; }
	sf::Vector2f getPosition() const { return sprite.getPosition(); }
	int getSpeed() const { return unitStats.speed; }
	sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }

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

