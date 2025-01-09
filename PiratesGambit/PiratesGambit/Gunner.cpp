#include "Gunner.h"

void Gunner::init()
{
	sprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	sprite.setTextureRect(rectSourceSprite);

	sprite.setScale(3.5, 3.5);
	sprite.setOrigin(16, 24);

	updateUnitAmount(unitStats.stackSize);

	unitStats.speed = 4;
}

void Gunner::update(float _dt)
{
	animateSprite(_dt);
	if(Utility::magnitude(velocity.x, velocity.y) > 0)
	{
		currentState = WALK;
		if (velocity.x < 0) sprite.setScale(-3.5, 3.5);
		else sprite.setScale(3.5, 3.5);
	}else
	{
		currentState = IDLE;
	}
}

void Gunner::animateSprite(float _dt)
{
	switch (currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(sprite, animationState,idleAnimation, 4, 0, _dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(sprite, animationState,walkAnimation, 6, 1, _dt);
		break;
	}
}
