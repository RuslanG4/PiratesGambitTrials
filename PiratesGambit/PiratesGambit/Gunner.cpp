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

	sprite.setScale(3, 3);
	sprite.setOrigin(16, 24);

	speed = 4;
}

void Gunner::update(float _dt)
{
	animateSprite(_dt);
	if(Utility::magnitude(velocity.x, velocity.y) > 0)
	{
		currentState = WALK;
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
		Animator::getInstance().AnimateSprite(sprite, animationState, 4, 0, _dt);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(sprite, animationState, 6, 1, _dt);
		break;
	}
}
