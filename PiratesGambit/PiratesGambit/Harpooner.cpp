#include "Harpooner.h"

void Harpooner::init()
{
	sprite.setTexture(TextureManager::getInstance().getTexture("HARPOONER"));

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 32;
	rectSourceSprite.width = 32;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	sprite.setTextureRect(rectSourceSprite);

	if (unitInformation.allegiance != HUMAN_PLAYER) {
		scaleX = -scaleX;
		facingDirection = -facingDirection;
	}
	sprite.setScale(scaleX, scaleY);
	sprite.setOrigin(16, 24);

	updateUnitAmount(unitStats.stackSize);
}

void Harpooner::update(float _dt)
{
	if (unitStats.isActive) {
		animateSprite(_dt);
		if (currentState != ATTACK && currentState != DEATH && currentState != DAMAGED) {
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
}

void Harpooner::animateSprite(float _dt)
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
		Animator::getInstance().AnimateShoot(sprite, animationState, attackAnimation, shootBullet,1, 10, 3, _dt);
		if (shootBullet)
		{
			bulletDirection = targetPosition - sprite.getPosition();
			bulletDirection = Utility::unitVector2D(bulletDirection);
			BulletFactory::getInstance().createHarpoon(sprite.getPosition(), bulletDirection);
			ParticleManager::getInstance().CreateShootParticle(sf::Vector2f(sprite.getPosition().x + (30 * facingDirection), sprite.getPosition().y + 10));
			shootBullet = false;
		}
		if (attackAnimation)
		{
			currentState = IDLE;
			animationState.elapsedTime = 0;
			sprite.setScale(scaleX, scaleY);
		}
		break;
	case DAMAGED:
		Animator::getInstance().AnimateSprite(sprite, animationState, damagedAnimation, 2, 5, _dt);
		if (damagedAnimation)
		{
			currentState = IDLE;
		}
		break;
	case DEATH:
		Animator::getInstance().AnimateSprite(sprite, animationState, deathAnimation, 5, 6, _dt);
		if (deathAnimation)
		{
			unitStats.isActive = false;
			unitAmount->renderUnitAmount = false;
			Animator::getInstance().AnimateDeath(sprite, 4, 6);
		}
		break;
	}
}
