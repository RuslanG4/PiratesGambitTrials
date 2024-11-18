#pragma once
#include"Includes.h"

class BoatController
{
public:
	BoatController(sf::Vector2f _pos) : m_currentPosition(_pos)
	{
	}
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();

	void update_speed();
	void deflect();

	sf::Vector2f move(double dt);


	float getRotation() const { return m_rotation; }
	double getSpeed() const { return m_speed; }
	sf::Vector2f getVelocity() const { return vel; }
	sf::Vector2f getPreviousPosition() const { return m_previousPosition; }
	sf::Vector2f getPosition() const { return m_currentPosition; }

	void setSpeed(const double& _speed) { m_speed = _speed; }
	void setCurrentPosition(const sf::Vector2f& _pos) { m_currentPosition = _pos; }

private:
	sf::Vector2f vel;
	sf::Vector2f m_currentPosition;
	sf::Vector2f m_previousPosition;

	double m_speed{ 0.0 };
	float m_rotation{ 0.0 };

	const double MAX_REVERSE_SPEED = -40; //for movement
	const double MAX_FORWARD_SPEED = 40;
};

