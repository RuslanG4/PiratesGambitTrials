#include "ShotParticle.h"

ShotParticle::ShotParticle(sf::Vector2f _pos)
{
	particleSpriteSheet.setTexture(TextureManager::getInstance().getTexture("SHOOT_PARTICLES"));
	particleSpriteSheet.setOrigin(32, 32);
	particleSpriteSheet.setPosition(_pos);

	sf::IntRect rectSourceSprite;
	rectSourceSprite.height = 64;
	rectSourceSprite.width = 64;
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	particleSpriteSheet.setTextureRect(rectSourceSprite);

}

void ShotParticle::Update(float _dt)
{
	Animator::getInstance().AnimateParticle(particleSpriteSheet, animationState, animationFinish, 11, 5, 64, 64, _dt);
}
