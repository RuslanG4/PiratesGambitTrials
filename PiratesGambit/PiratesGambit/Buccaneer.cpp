#include "Buccaneer.h"

void Buccaneer::init()
{
	sprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	sprite.setTextureRect(rectSourceSprite);

	sprite.setScale(3.5, 3.5);
	sprite.setOrigin(16, 24);

	updateUnitAmount(currentStack);

	speed = 4;
}

void Buccaneer::update(float _dt)
{
	animateSprite(_dt);
	if (currentState != ATTACK) {
		if (Utility::magnitude(velocity.x, velocity.y) > 0)
		{
			currentState = WALK;
		}
		else
		{
			currentState = IDLE;
		}
	}
}

void Buccaneer::animateSprite(float _dt)
{
	switch (currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(sprite, animationState,idleAnimation, 4, 0, _dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(sprite, animationState,walkAnimation, 6, 1, _dt);
		break;
	case ATTACK:
		Animator::getInstance().AnimateSprite(sprite, animationState, attackAnimation, 5, 3, _dt);
		if(attackAnimation)
		{
			currentState = IDLE;
			animationState.elapsedTime = 0;
		}
		break;
	}
}

