#include "PlayerController.h"

void PlayerController::deflect()
{
	// Reverse the velocity and scale it down to simulate deflection
	vel = { -vel.x * 2.75f, -vel.y * 2.75f };

	// Adjust the position slightly to move the player out of the collision area
	m_currentPosition = m_currentPosition + vel; // Small adjustment
}

sf::Vector2f PlayerController::move(double dt)
{
	const float speed = 1.0f; 
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
