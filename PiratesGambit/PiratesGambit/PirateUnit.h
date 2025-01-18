#pragma once
#include"Includes.h"
#include"Animator.h"
#include "TextureManager.h"
#include"Enums.h"
#include"UnitAmount.h"

struct UnitStats
{
	int initiative;
	float speed;
	int stackSize;
	float turnPoints = 0; 
	bool isActive = true;
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

	void addToCurrentStack(int _amount) { unitStats.stackSize += _amount; }
	int getStackSize() const { return unitStats.stackSize; }

	virtual void update(float _dt) = 0;
	virtual void animateSprite(float _dt) = 0;

	void updateUnitAmount(int _amount);
	void placeUnitAmountText();

	void moveUnit(sf::Vector2f _vel);
	void Attack();

	void render(const std::unique_ptr<sf::RenderWindow>& window) const;
	void placeUnit(sf::Vector2f _pos);
	void setCurrentNodeId(int _id) { nodeId = _id; }
	int getCurrentNodeId()const { return nodeId; }
	sf::Vector2f getPosition() const { return sprite.getPosition(); }
	int getSpeed() const { return unitStats.speed; }
	sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }

	UnitState currentState = IDLE;

	UnitStats unitStats;

	UnitInformation unitInformation;

protected:
	float scaleX = 3.5, scaleY = 3.5;
	int nodeId;
	sf::Sprite sprite;

	bool attackAnimation = false;
	bool walkAnimation;
	bool idleAnimation;

	AnimationState animationState;

	UnitAmount unitAmount;
	sf::Vector2f velocity;
};

