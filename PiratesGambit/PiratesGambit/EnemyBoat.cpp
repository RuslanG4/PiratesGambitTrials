#include "EnemyBoat.h"

void EnemyBoat::render(const std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(boatSprite);
}

void EnemyBoat::update(double dt)
{
}
