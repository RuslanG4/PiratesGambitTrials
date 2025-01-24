#include "BloodParticle.h"

BloodParticle::BloodParticle(sf::Vector2f _pos)
{
	particleSpriteSheet.setTexture(TextureManager::getInstance().getTexture("BLOOD_PARTICLES"));
	particleSpriteSheet.setOrigin(50, 50);
	particleSpriteSheet.setPosition(_pos);

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 50;
	rectSourceSprite.width = 50;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	particleSpriteSheet.setTextureRect(rectSourceSprite);

	particleSpriteSheet.setScale(2, 2);
}

void BloodParticle::Update(float _dt)
{
	Animator::getInstance().AnimateParticle(particleSpriteSheet, animationState, animationFinish, 21, 0, 100, 100, _dt);
}
