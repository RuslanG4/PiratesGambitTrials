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

	if (allegiance != RED_PLAYER) {
		scaleX = -scaleX;
	}
	sprite.setScale(scaleX, scaleY);
	sprite.setOrigin(16, 24);

	updateUnitAmount(unitStats.stackSize);

	unitStats.speed = 4;
}

void Gunner::update(float _dt)
{
	animateSprite(_dt);
	if (currentState != ATTACK) {
		if (Utility::magnitude(velocity.x, velocity.y) > 0)
		{
			currentState = WALK;
			if (velocity.x < 0) sprite.setScale(-3.5, 3.5);
			else sprite.setScale(3.5, 3.5);
		}
		else
		{
			currentState = IDLE;
			sprite.setScale(scaleX, scaleY);
		}
	}
}

void Gunner::animateSprite(float _dt)
{
	switch (currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(sprite, animationState, idleAnimation, 4, 0, _dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(sprite, animationState, walkAnimation, 6, 1, _dt);
		break;
	case ATTACK:
		Animator::getInstance().AnimateSprite(sprite, animationState, attackAnimation, 7, 3, _dt);
		if (attackAnimation)
		{
			currentState = IDLE;
			animationState.elapsedTime = 0;
			sprite.setScale(scaleX, scaleY);
		}
		break;
	}
}
