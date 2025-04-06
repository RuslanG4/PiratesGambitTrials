#pragma once
#include "AnimatedCharacterIcon.h"
class BirdIcon :
    public AnimatedCharacterIcon
{
public:
	BirdIcon(sf::Vector2f _pos)
	{
		sprite.setTexture(TextureManager::getInstance().getTexture("BIRD"));
		background.setTexture(TextureManager::getInstance().getTexture("ARMY_MENU_UI"));

		sf::IntRect rectSourceSprite;
		rectSourceSprite.height = 64;
		rectSourceSprite.width = 64;
		rectSourceSprite.left = 0;
		rectSourceSprite.top = 0;
		sprite.setTextureRect(rectSourceSprite);

		sprite.setScale(4.5, 4.6);
		sprite.setOrigin(32, 32);

		sprite.setPosition(_pos);

		background.setOrigin(28, 28);
		background.setScale(4, 4);
		background.setPosition(_pos);
	}
	void Update(float _dt) override;

private:
	bool idleAnimation{ false };
};

