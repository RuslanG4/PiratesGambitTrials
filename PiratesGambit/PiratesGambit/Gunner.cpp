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

	sprite.setScale(2, 2);
	sprite.setOrigin(16, 24);
}

void Gunner::update()
{
	animateSprite();
}

void Gunner::animateSprite()
{
	switch (currentState)
	{
	case IDLE:
		Animator::getInstance().AnimateSprite(sprite, 4, 0);
		break;
	case WALK:
		Animator::getInstance().AnimateSprite(sprite, 6, 1);
		break;
	}
}
