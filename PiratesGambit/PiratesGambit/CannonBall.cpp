#include "CannonBall.h"



CannonBall::CannonBall(sf::Vector2f _pos, sf::Vector2f _vel) : position(_pos), velocity(_vel)
{
	init();
}

void CannonBall::init()
{
	body.setTexture(TextureManager::getInstance().getTexture("CANNON_BALL"));
	body.setOrigin(5, 5);
	body.setScale(0.5, 0.5);
	body.setPosition(position);
}

void CannonBall::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	if (isActive) {
		window->draw(body);
	}
}

void CannonBall::update()
{
	if (isActive) {
		position += velocity;
		body.setPosition(position);
	}
}

void CannonBall::fire(sf::Vector2f _position, sf::Vector2f _velocity)
{
	position = _position;
	body.setPosition(position);

	velocity = _velocity * force;

	isActive = true;
}
