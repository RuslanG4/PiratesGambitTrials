#include "Particle.h"

void Particle::Render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(particleSpriteSheet);
}
