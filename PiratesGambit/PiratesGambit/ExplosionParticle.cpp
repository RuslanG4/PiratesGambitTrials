#include "ExplosionParticle.h"

ExplosionParticle::ExplosionParticle(sf::Vector2f _pos)
{
	particleSpriteSheet.setTexture(TextureManager::getInstance().getTexture("EXPLOSION_PARTICLE"));
	particleSpriteSheet.setOrigin(24, 24);
	particleSpriteSheet.setPosition(_pos);

	particleSpriteSheet.setScale(2, 2);

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 48;
	rectSourceSprite.width = 48;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	particleSpriteSheet.setTextureRect(rectSourceSprite);
}

void ExplosionParticle::Update(float _dt)
{
	Animator::getInstance().AnimateParticle(particleSpriteSheet, animationState, animationFinish, 7, 0, 48, 48, _dt);
}
