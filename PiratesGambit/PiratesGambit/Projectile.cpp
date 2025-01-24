#include "Projectile.h"

void Projectile::update()
{
	if (isActive) {
		position += velocity;
		body.setPosition(position);
	}
}

void Projectile::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	if (isActive) {
		window->draw(body);
	}
}

void Projectile::fire(sf::Vector2f _position, sf::Vector2f _velocity)
{
	position = _position;
	body.setPosition(position);

	velocity = _velocity * force;

	isActive = true;
}
