#include "BoatController.h"

void BoatController::increaseSpeed()
{
	m_speed += 2.5;
}

void BoatController::decreaseSpeed()
{
	m_speed -= 2.5;
}

void BoatController::increaseRotation()
{
	previousRotation = m_rotation;
	m_rotation += 1.25;
	if (m_rotation >= 360.0)
	{
		m_rotation = 0;
	}
}

void BoatController::decreaseRotation()
{
	previousRotation = m_rotation;
	m_rotation -= 1.25;
	if (m_rotation <= 0.0)
	{
		m_rotation = 359.0;
	}
}

void BoatController::update_speed()
{
	m_speed = std::clamp(m_speed, MAX_REVERSE_SPEED, MAX_FORWARD_SPEED);
	m_speed = m_speed * 0.995;
}

void BoatController::deflect()
{
	m_speed = 0;
	m_rotation = previousRotation;
	vel = { -vel.x, -vel.y };
	m_currentPosition = m_currentPosition + vel;
}

sf::Vector2f BoatController::move(double dt)
{
	vel.x = std::cos(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);
	vel.y = std::sin(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);

	sf::Vector2f newPosition{ vel.x, vel.y };

	return newPosition;
}

