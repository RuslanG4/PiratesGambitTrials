#pragma once
#include"Includes.h"

class PlayerController
{
public:
	PlayerController(sf::Vector2f _pos) : m_currentPosition(_pos)
	{
	}

	void deflect();

	sf::Vector2f move(double dt);

	void setLandVelocity(sf::Vector2f _vel);

	sf::Vector2f getVelocity() const { return vel; }
	sf::Vector2f getPosition() const { return m_currentPosition; }

	void setCurrentPosition(const sf::Vector2f& _pos) { m_currentPosition = _pos; }

private:
	const float speed = 1.0f;

	sf::Vector2f vel;
	sf::Vector2f m_currentPosition;
};

