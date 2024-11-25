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

	virtual void update() = 0;
	virtual void animateSprite() = 0;

	void render(sf::RenderWindow& _win) const;
	void placeUnit(sf::Vector2f _pos) { sprite.setPosition(_pos); }
protected:
	sf::Sprite sprite;
	UnitState currentState = IDLE;
private:
};

