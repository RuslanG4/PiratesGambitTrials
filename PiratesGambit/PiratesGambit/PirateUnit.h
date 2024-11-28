#pragma once
#include"Includes.h"
#include"Animator.h"
#include "TextureManager.h"
#include"Enums.h"

class PirateUnit
{
public:
	virtual ~PirateUnit() = default;
	PirateUnit() = default;

	virtual void update(float _dt) = 0;
	virtual void animateSprite(float _dt) = 0;

	void moveUnit(sf::Vector2f _vel);

	void render(sf::RenderWindow& _win) const;
	void placeUnit(sf::Vector2f _pos) { sprite.setPosition(_pos); }
	void setCurrentNodeId(int _id) { nodeId = _id; }
	int getCurrentNodeId()const { return nodeId; }
	sf::Vector2f getPosition() const { return sprite.getPosition(); }
	int getSpeed() const { return speed; }
protected:
	int initiative;
	int nodeId;
	int speed;
	AnimationState animationState;
	sf::Sprite sprite;
	UnitState currentState = IDLE;

	sf::Vector2f velocity;
private:
};

