#include "PlayerController.h"

void PlayerController::increaseSpeed()
{
	m_speed += 5;
}

void PlayerController::decreaseSpeed()
{
	m_speed -= 5;
}

void PlayerController::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void PlayerController::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}

void PlayerController::updateSpeed()
{
	m_speed = std::clamp(m_speed, MAX_REVERSE_SPEED, MAX_FORWARD_SPEED);
	m_speed = m_speed * 0.995;
}

void PlayerController::deflect()
{
	m_speed = 0;
	vel = { -vel.x , -vel.y };
	m_currentPosition = m_currentPosition + vel;
}

sf::Vector2f PlayerController::move(double dt)
{
	vel.x = std::cos(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);
	vel.y = std::sin(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);

	sf::Vector2f newPosition = { m_currentPosition.x + vel.x, m_currentPosition.y + vel.y };

	return newPosition;
}
