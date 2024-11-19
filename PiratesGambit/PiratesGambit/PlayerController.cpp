#include "PlayerController.h"

sf::Vector2f PlayerController::move(double dt)
{
	sf::Vector2f newPosition = vel * speed;

	return newPosition;
}

void PlayerController::setLandVelocity(sf::Vector2f _vel)
{
	if (_vel.x != 0 || _vel.y != 0)
	{
		float magnitude = std::sqrt(_vel.x * _vel.x + _vel.y * _vel.y);
		vel = _vel /= magnitude;
	}else
	{
		vel = { 0,0 };
	}
}
