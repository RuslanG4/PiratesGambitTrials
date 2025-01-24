#pragma once
#include"Includes.h"
#include"Animator.h"
#include "TextureManager.h"

class Particle
{
public:
	virtual ~Particle() = default;
	virtual void Update(float _dt) = 0;
	void Render(const std::unique_ptr<sf::RenderWindow>& window) const;

	bool isMarkedForDeletion() const { return animationFinish; }
protected:
	sf::Sprite particleSpriteSheet;
	AnimationState animationState;
	bool animationFinish{false};
	
};

