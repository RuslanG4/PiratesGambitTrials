#pragma once
#include"Includes.h"
#include "PirateUnit.h"

class AnimatedCharacterIcon
{
public:
	virtual ~AnimatedCharacterIcon() = default;
	AnimatedCharacterIcon() = default;

	void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
	virtual void Update(float _dt) = 0;

protected:
	sf::Sprite sprite;
	sf::Sprite background;

	AnimationState animationState;
};

