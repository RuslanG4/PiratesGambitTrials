#pragma once
#include"Includes.h"

class PlayerController
{
public:
	PlayerController(sf::Vector2f _pos) : m_currentPosition(_pos)
	{
	}
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();

	void updateSpeed();
	void deflect();

	sf::Vector2f move(double dt);
	float getRotation() const { return m_rotation; }
	float getSpeed() const { return m_speed; }
	sf::Vector2f getVelocity() const { return vel; }
	sf::Vector2f getPreviousPosition() const { return m_previousPosition; }
	sf::Vector2f getPosition() const { return m_currentPosition; }

	void setSpeed(const float& _speed) { m_speed = _speed; }
	void setCurrentPosition(const sf::Vector2f& _pos) { m_currentPosition = _pos; }

private:
	sf::Vector2f vel;
	sf::Vector2f m_currentPosition;
	sf::Vector2f m_previousPosition;

	float m_speed{ 0.0 };
	float m_rotation{ 0.0 };

	const float MAX_REVERSE_SPEED = -40; //for movement
	const float MAX_FORWARD_SPEED = 40;
};

