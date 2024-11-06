#include "Player.h"

Player::Player()
{
	body.setPosition(sf::Vector2f(100, 100));
	body.setOrigin(56, 33);
	body.setScale(0.5, 0.5);

	initCamera();
}

void Player::initCamera()
{
	playerCamera.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
	playerCamera.setCenter(body.getPosition());
}

void Player::update(double dt)
{
	move(dt);

	handleKeyInput();

	m_speed = std::clamp(m_speed, MAX_REVERSE_SPEED, MAX_FORWARD_SPEED);
	m_speed = m_speed * 0.995;

	//constantly rotates and sets rotation
	body.setRotation(m_rotation);

	playerCamera.setCenter(body.getPosition());
}

void Player::render(sf::RenderWindow& window) const
{
	window.draw(body);
	for (Node* node : updateableArea.getUpdateableNodes())
	{
		if (node != nullptr) {
			window.draw(*(node->debugShape));
		}
	}
}

void Player::handleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
}

void Player::move(double dt)
{

	vel.x = std::cos(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);
	vel.y = std::sin(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);

	newpos.x = body.getPosition().x + vel.x;
	newpos.y = body.getPosition().y + vel.y;

	body.setPosition(newpos);
}

void Player::increaseSpeed()
{
	m_speed += 5;
}

void Player::decreaseSpeed()
{
	m_speed -= 5;
}

void Player::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Player::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}

void Player::updateUpdateableArea(Node*& _startNode, int depth)
{
	updateableArea.updateVisibleNodes(_startNode, depth);
}
