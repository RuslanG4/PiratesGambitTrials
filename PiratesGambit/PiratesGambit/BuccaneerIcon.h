#pragma once
#include "AnimatedCharacterIcon.h"
class BuccaneerIcon :
    public AnimatedCharacterIcon
{
public:
	BuccaneerIcon(sf::Vector2f _pos)
	{
		sprite.setTexture(TextureManager::getInstance().getTexture("BUCCANEER"));

		sf::IntRect rectSourceSprite;
		rectSourceSprite.height = 32;
		rectSourceSprite.width = 32;
		rectSourceSprite.left = 0;
		rectSourceSprite.top = 0;
		sprite.setTextureRect(rectSourceSprite);

		sprite.setScale(9,9);
		sprite.setOrigin(16, 24);

		sprite.setPosition(_pos);
	}
	void Update(float _dt) override;

private:
	bool idleAnimation{ false };
};

