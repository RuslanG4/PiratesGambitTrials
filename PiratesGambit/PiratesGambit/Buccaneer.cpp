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

	sprite.setScale(3, 3);
	sprite.setOrigin(16, 24);

	speed = 4;
}

void Buccaneer::animateSprite(float _dt)
{
	switch (currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(sprite, animationState, 4, 0, _dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(sprite, animationState, 6, 1, _dt);
		break;
	}
}

void Buccaneer::update(float _dt)
{
	animateSprite(_dt);
}
