#include "Projectile.h"

void Projectile::update(double dt)
{
	if (isActive) {
		prevPosition = position;
		position += velocity;
		body.setPosition(position);

		ParticleManager::getInstance().CreateCannonBallTrailParticle(position, -velocity);

		lifetime -= dt * 0.001;
		if (lifetime <= 0) {
			isActive = false;
		}
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
