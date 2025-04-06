#include "BirdUnit.h"

void BirdUnit::init()
{
	sprite.setTexture(TextureManager::getInstance().getTexture("BIRD"));

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 64;
	rectSourceSprite.width = 64;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	sprite.setTextureRect(rectSourceSprite);

	scaleX = 1.75;
	scaleY = 1.75;

	if (unitInformation.allegiance != HUMAN_PLAYER) {
		scaleX = -scaleX;
	}
	sprite.setScale(scaleX, scaleY);
	sprite.setOrigin(32, 32);

	updateUnitAmount(unitStats.stackSize);
}

void BirdUnit::animateSprite(float _dt)
{
	switch (currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(sprite, animationState, idleAnimation, 5, 3, _dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(sprite, animationState, walkAnimation, 4, 4, _dt);
		break;
	case ATTACK:
		Animator::getInstance().AnimateSprite(sprite, animationState, attackAnimation, 6, 7, _dt);
		if (attackAnimation)
		{
			currentState = IDLE;
			animationState.elapsedTime = 0;
			sprite.setScale(scaleX, scaleY);
		}
		break;
	case DAMAGED:
		Animator::getInstance().AnimateSprite(sprite, animationState, damagedAnimation, 4, 9, _dt);
		if (damagedAnimation)
		{
			currentState = IDLE;
			animationState.elapsedTime = 0;
			animationState.currentFrame = 0;
		}
		break;
	case DEATH:
		Animator::getInstance().AnimateSprite(sprite, animationState, deathAnimation, 11, 10, _dt);
		if (deathAnimation)
		{
			unitStats.isActive = false;
			unitAmount->renderUnitAmount = false;
			Animator::getInstance().AnimateDeath(sprite, 3, 5);
		}
		break;
	}
}

void BirdUnit::update(float _dt)
{
	if (unitStats.isActive) {
		animateSprite(_dt);
		if (currentState != ATTACK && currentState != DEATH && currentState != DAMAGED) {
			if (Utility::magnitude(velocity.x, velocity.y) > 0)
			{
				currentState = WALK;
				if (velocity.x < 0) sprite.setScale(-1.75, 1.75);
				else sprite.setScale(1.75, 1.75);
			}
			else
			{
				currentState = IDLE;
				sprite.setScale(scaleX, scaleY);
			}
		}
	}
}
