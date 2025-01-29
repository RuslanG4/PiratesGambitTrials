#pragma once
#include "AnimatedCharacterIcon.h"
#include "Gunner.h"

class GunnerIcon :
    public AnimatedCharacterIcon
{
	public:
		GunnerIcon(sf::Vector2f _pos)
		{
			sprite.setTexture(TextureManager::getInstance().getTexture("GUNNER"));

			sf::IntRect rectSourceSprite;
			rectSourceSprite.height = 32;
			rectSourceSprite.width = 32;
			rectSourceSprite.left = 0;
			rectSourceSprite.top = 0;
			sprite.setTextureRect(rectSourceSprite);

			sprite.setScale(9, 9);
			sprite.setOrigin(16, 24);

			sprite.setPosition(_pos);
		}
		void Update(float _dt) override;

private:
	bool idleAnimation{false};
};

