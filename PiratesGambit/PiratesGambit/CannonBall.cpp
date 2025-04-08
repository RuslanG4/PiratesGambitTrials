#include "CannonBall.h"


CannonBall::CannonBall(sf::Vector2f _pos, sf::Vector2f _vel, float _lifetime)
{
	position = _pos;
	velocity = _vel;

	lifetime = _lifetime;
}

void CannonBall::init()
{
	body.setTexture(TextureManager::getInstance().getTexture("CANNON_BALL"));
	body.setOrigin(8, 8);
	body.setScale(1.5, 1.5);
	body.setPosition(position);
}
